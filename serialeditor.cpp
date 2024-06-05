#include "serialeditor.h"
#include "ui_serialeditor.h"
#include <QFile>
#include <QMessageBox>

const QString FILE_PATH = "proinfo.bin";
const int BUFFER_SIZE = 0x300000;

SerialEditor::SerialEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SerialEditor)
{
    ui->setupUi(this);

    loadFile();
    parseFile();
}

SerialEditor::~SerialEditor()
{
    delete ui;
}

void SerialEditor::loadFile()
{
    QFile file(FILE_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return;
    }
    fileData = file.read(BUFFER_SIZE);
    file.close();
}

void SerialEditor::parseFile()
{
    if (fileData.size() < BUFFER_SIZE) {
        QMessageBox::critical(this, "Ошибка", "Некорректный размер файла");
        return;
    }

    // Извлечение значений из бинарного файла
    QString value1 = QString::fromUtf8(fileData.mid(0x10, 16).trimmed());
    QString value2 = QString::fromUtf8(fileData.mid(0x20, 16).trimmed());

    // Установка значений в QLineEdit
    ui->lineEdit_value1->setText(value1);
    ui->lineEdit_value2->setText(value2);
}

void SerialEditor::saveFile()
{
    QString value1 = ui->lineEdit_value1->text();
    QString value2 = ui->lineEdit_value2->text();

    if (value1.size() > 16 || value2.size() > 16) {
        QMessageBox::critical(this, "Ошибка", "Введенные значения слишком длинные");
        return;
    }

    // Замена значений в бинарном файле
    fileData.replace(0x10, 16, value1.toUtf8().leftJustified(16, '\0'));
    fileData.replace(0x20, 16, value2.toUtf8().leftJustified(16, '\0'));

    QFile file(FILE_PATH);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }
    file.write(fileData);
    file.close();

    QMessageBox::information(this, "Успех", "Файл успешно сохранен");
}

void SerialEditor::on_saveButton_clicked()
{
    saveFile();
}
