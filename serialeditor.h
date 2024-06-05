#ifndef SERIALEDITOR_H
#define SERIALEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SerialEditor;
}
QT_END_NAMESPACE

class SerialEditor : public QMainWindow
{
    Q_OBJECT

public:
    SerialEditor(QWidget *parent = nullptr);
    ~SerialEditor();

private:
    Ui::SerialEditor *ui;
    QByteArray fileData;

    void loadFile();
    void parseFile();
    void saveFile();

private slots:
    void on_saveButton_clicked();
};
#endif // SERIALEDITOR_H
