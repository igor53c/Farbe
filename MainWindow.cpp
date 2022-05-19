#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    scrollSlider();

    setTransparency();
}

void MainWindow::on_btnBeenden_clicked()
{
    close();
}

void MainWindow::on_sliderRot_valueChanged(int)
{
    scrollSlider();
}

void MainWindow::on_sliderGruen_valueChanged(int)
{
    scrollSlider();
}

void MainWindow::on_sliderBlau_valueChanged(int)
{
    scrollSlider();
}

void MainWindow::scrollSlider()
{
    QPalette p = this->palette();

    int rot = ui->sliderRot->value();
    int gruen = ui->sliderGruen->value();
    int blau = ui->sliderBlau->value();

    p.setColor(QPalette::Window, QColor(rot, gruen, blau));

    p.setColor(QPalette::WindowText, rot * 0.3 + gruen * 0.6 + blau * 0.1 > 186 ? Qt::black : Qt::white);

    ui->textDezRot->setText(QString::number(rot));
    ui->textHexRot->setText(QString("X'%1'").arg(rot, 2, 16, QChar('0')).toUpper());

    ui->textDezGruen->setText(QString::number(gruen));
    ui->textHexGruen->setText(QString("X'%1'").arg(gruen, 2, 16, QChar('0')).toUpper());

    ui->textDezBlau->setText(QString::number(blau));
    ui->textHexBlau->setText(QString("X'%1'").arg(blau, 2, 16, QChar('0')).toUpper());

    this->setPalette(p);
}

void MainWindow::setTransparency()
{
    this->setWindowOpacity(1 - (ui->sliderTransparenz->value() / 100.0));
    ui->textTransparentz->setText(QString::number(ui->sliderTransparenz->value()) + " %");
}

void MainWindow::saveToClipboard()
{
    QString hexColor = QString("#%1%2%3")
                           .arg(ui->sliderRot->value(), 2, 16, QChar('0').toUpper())
                           .arg(ui->sliderGruen->value(), 2, 16, QChar('0').toUpper())
                           .arg(ui->sliderBlau->value(), 2, 16, QChar('0').toUpper());

    QString colorString = "// Farbmischer(Rot, Grün, Blau):\n";

    colorString += QString("// QColor newColor = new QColor(%1, %2, %3)\n")
                       .arg(ui->sliderRot->value())
                       .arg(ui->sliderGruen->value())
                       .arg(ui->sliderBlau->value());

    colorString += "// " + hexColor;

    QClipboard* clipBoard = QApplication::clipboard();

    clipBoard->setText(colorString);
}

void MainWindow::on_sliderTransparenz_valueChanged(int)
{
    setTransparency();
}


void MainWindow::on_btnZwischen_clicked()
{
    saveToClipboard();
}

void MainWindow::on_textDezRot_returnPressed()
{
    setColor(ui->sliderRot, ui->textDezRot);
}

void MainWindow::on_textDezRot_editingFinished()
{
    setColor(ui->sliderRot, ui->textDezRot);
}

void MainWindow::on_textDezGruen_returnPressed()
{
    setColor(ui->sliderGruen, ui->textDezGruen);
}

void MainWindow::on_textDezGruen_editingFinished()
{
    setColor(ui->sliderGruen, ui->textDezGruen);
}

void MainWindow::on_textDezBlau_returnPressed()
{
    setColor(ui->sliderBlau, ui->textDezBlau);
}

void MainWindow::on_textDezBlau_editingFinished()
{
    setColor(ui->sliderBlau, ui->textDezBlau);
}

void MainWindow::setColor(QSlider* slider, QLineEdit* lineEdit)
{
    int color = slider->value();

    bool bOK;

    int newColor = lineEdit->text().toInt(&bOK);

    if(!bOK || newColor < MIN_COLOR || newColor > MAX_COLOR)
    {
        QMessageBox::critical(this, "Fehler", "Der zulässige Wert liegt zwischen " + QString::number(MIN_COLOR) +
                                                  " und " + QString::number(MAX_COLOR) + "!");

        lineEdit->setText(QString::number(color));
    }
    else
        slider->setSliderPosition(newColor);
}
