#include <QApplication>
#include <QInputMethodEvent>

#include <cstdio>

#include "Scintilla.h"
#include "ScintillaEdit.h"

namespace {

int Fail(const char *message, sptr_t expected, sptr_t actual) {
    std::fprintf(stderr, "%s: expected %td, got %td\n", message, expected, actual);
    return 1;
}

int FailText(const char *message, const QByteArray &expected, const QByteArray &actual) {
    std::fprintf(stderr, "%s: expected [%s], got [%s]\n", message, expected.constData(), actual.constData());
    return 1;
}

QInputMethodEvent HangulPreeditEvent(const QString &preedit) {
    const QList<QInputMethodEvent::Attribute> attributes {
        QInputMethodEvent::Attribute(QInputMethodEvent::Cursor, preedit.size(), 0, QVariant())
    };
    return QInputMethodEvent(preedit, attributes);
}

QByteArray TextOf(ScintillaEdit &editor) {
    return editor.getText(editor.length() + 1);
}

int VerifyHangulFollowedByCommit(const QString &commitText, const QByteArray &expectedText) {
    ScintillaEdit editor;
    editor.setCodePage(SC_CP_UTF8);
    editor.setText(QString::fromUtf8(u8"가나다").toUtf8().constData());
    editor.gotoPos(editor.length());

    QInputMethodEvent preedit = HangulPreeditEvent(QString::fromUtf8(u8"라"));
    QApplication::sendEvent(&editor, &preedit);

    QInputMethodEvent commit;
    commit.setCommitString(commitText, 0, 0);
    QApplication::sendEvent(&editor, &commit);

    const QByteArray actualText = TextOf(editor);
    if (actualText != expectedText) {
        return FailText("hangul preedit should be preserved before trailing commit text", expectedText, actualText);
    }
    return 0;
}

}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    const QByteArray hangulThenPeriod = QString::fromUtf8(u8"가나다라.").toUtf8();
    const QByteArray hangulThenDigit = QString::fromUtf8(u8"가나다라1").toUtf8();
    const QByteArray committedHangul = QString::fromUtf8(u8"가나다라").toUtf8();

    ScintillaEdit editor;
    editor.setCodePage(SC_CP_UTF8);
    editor.setText("");
    editor.resize(400, 200);
    editor.show();
    editor.grabFocus();
    app.processEvents();

    const QList<QInputMethodEvent::Attribute> attributes {
        QInputMethodEvent::Attribute(QInputMethodEvent::Cursor, 1, 0, QVariant())
    };
    QInputMethodEvent event(QStringLiteral("하"), attributes);
    QApplication::sendEvent(&editor, &event);

    const sptr_t expectedLength = 3;
    if (editor.length() != expectedLength) {
        return Fail("preedit length", expectedLength, editor.length());
    }
    if (editor.currentPos() != expectedLength) {
        return Fail("hangul preedit caret should stay at end of composition", expectedLength, editor.currentPos());
    }

    if (VerifyHangulFollowedByCommit(QStringLiteral("."), hangulThenPeriod) != 0) {
        return 1;
    }
    if (VerifyHangulFollowedByCommit(QStringLiteral("1"), hangulThenDigit) != 0) {
        return 1;
    }
    if (VerifyHangulFollowedByCommit(QString::fromUtf8(u8"라"), committedHangul) != 0) {
        return 1;
    }

    return 0;
}
