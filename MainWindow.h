#pragma once

#include <QMainWindow>
#include <QClipboard>
#include <QMessageBox>
#include <QSlider>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sliderRot_valueChanged(int value);

    void on_btnBeenden_clicked();

    void on_sliderGruen_valueChanged(int value);

    void on_sliderBlau_valueChanged(int value);

    void on_sliderTransparenz_valueChanged(int value);

    void on_btnZwischen_clicked();

    void on_textDezRot_returnPressed();

    void on_textDezRot_editingFinished();

    void on_textDezGruen_returnPressed();

    void on_textDezGruen_editingFinished();

    void on_textDezBlau_returnPressed();

    void on_textDezBlau_editingFinished();

private:
    Ui::MainWindow *ui;

    const int MIN_COLOR = 0;
    const int MAX_COLOR = 255;

    void init();

    void scrollSlider();

    void setTransparency();

    void saveToClipboard();

    void setColor(QSlider*, QLineEdit*);
};
