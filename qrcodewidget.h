#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class QRCodeWidget : public QWidget
{
    Q_OBJECT

public:
    QRCodeWidget(QWidget *parent = 0);
    ~QRCodeWidget() = default;

protected:
    void contextMenuEvent(QContextMenuEvent* event);

private:
    QLabel* label;
    QLineEdit* lineEdit;
};

#endif // QRCODEWIDGET_H
