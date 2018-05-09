#include "qrcodewidget.h"

#include <QMenu>
#include <QPixmap>
#include <QLayout>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QIcon>
#include <QApplication>
#include <QStyle>

#include "QZXing"

QRCodeWidget::QRCodeWidget(QWidget *parent)
    : QWidget(parent)
{
    static const QString initialString ("Hello World.");

    label = new QLabel;
    lineEdit = new QLineEdit;

    connect(lineEdit, &QLineEdit::textChanged, [this](const QString& str){
        auto image = QZXing::encodeData(str,
                                        QZXing::EncoderFormat::EncoderFormat_QR_CODE,
                                        QSize(240, 240),
                                        QZXing::EncodeErrorCorrectionLevel::EncodeErrorCorrectionLevel_M);
        label->setPixmap(QPixmap::fromImage(image));
    });

    lineEdit->setText(initialString);
    lineEdit->setClearButtonEnabled(true);

    auto layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);

    setLayout(layout);
}

void QRCodeWidget::contextMenuEvent(QContextMenuEvent* event)
{
    auto saveAction = new QAction("Save Image", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton)));

    connect(saveAction, &QAction::triggered, [this](){
        auto line = lineEdit->text().remove(QRegExp("[^a-zA-Z0-9\\d\\s]")).replace(" ", "");
        auto filename = QFileDialog::getSaveFileName(this,
                                                     "Save QR Code Image",
                                                     line,
                                                     "PNG (*.png)");
        if (!filename.isEmpty())
            label->pixmap()->save(filename);
    });

    QMenu menu(this);
    menu.addAction(saveAction);
    menu.exec(event->globalPos());
}
