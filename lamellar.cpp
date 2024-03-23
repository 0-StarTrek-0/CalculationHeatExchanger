#include "lamellar.h"
#include "Solution.h"
#include "ui_lamellar.h"

#include <QVariant>

Lamellar::Lamellar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lamellar)
{
    ui->setupUi(this);
    control();
}

Lamellar::~Lamellar()
{
    delete ui;
}

void Lamellar::control()
{
    ui->line_hot_T1->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_hot_T2->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_cold_T1->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_cold_T2->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_hot_dmass->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->line_hot_pressure->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->line_cold_dmass->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9][0-9][0-9]"), this));
    ui->line_cold_pressure->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9][0-9][0-9]"), this));

    ui->line_F_heat->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_d_eq->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_F_channel->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_length_channel->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_h_gofr->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_step_gofr->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_width_channel->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_gap->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_delt_wall->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_length->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
    ui->line_width->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9][0-9]*\\.[0-9][0-9][0-9][0-9]"), this));
}

//////////////////////////////////////Меню//////////////////////////////////////////
void Lamellar::on_Exit_menu_triggered()
{
    QApplication::quit();
}

void Lamellar::on_Open_menu_triggered()
{
    QString File;
    File = QFileDialog::getOpenFileName(this, "Открыть файл с исходными данными", "C:\\Users\\Ivan\\Desktop", "Текстовый документ (*.txt);");
    QFile outFile(File);
    if(outFile.open(QIODevice::ReadOnly| QIODevice::Text) ) {
        QTextStream stream(&outFile);
        //Горячий контур
        ui->cBox_material_hot->setCurrentIndex(stream.readLine().toInt());
        ui->line_hot_T1->setText(stream.readLine());
        ui->line_hot_T2->setText(stream.readLine());
        ui->line_hot_pressure->setText(stream.readLine());
        ui->line_hot_dmass->setText(stream.readLine());
        ui->cBox_cavity_hot->setCurrentIndex(stream.readLine().toInt());
        //Холодный контур
        ui->cBox_material_cold->setCurrentIndex(stream.readLine().toInt());
        ui->line_cold_T1->setText(stream.readLine());
        ui->line_cold_T2->setText(stream.readLine());
        ui->line_cold_pressure->setText(stream.readLine());
        ui->line_cold_dmass->setText(stream.readLine());
        ui->cBox_cavity_cold->setCurrentIndex(stream.readLine().toInt());
        //Параметры ТА пластин
        ui->cBox_material_heat_ex->setCurrentIndex(stream.readLine().toInt());
        ui->line_F_heat->setText(stream.readLine());
        ui->line_d_eq->setText(stream.readLine());
        ui->line_F_channel->setText(stream.readLine());
        ui->line_length_channel->setText(stream.readLine());
        ui->line_h_gofr->setText(stream.readLine());
        ui->line_step_gofr->setText(stream.readLine());
        ui->line_width_channel->setText(stream.readLine());
        ui->line_gap->setText(stream.readLine());
        ui->line_delt_wall->setText(stream.readLine());
        ui->line_length->setText(stream.readLine());
        ui->line_width->setText(stream.readLine());
        ui->cBox_current_type->setCurrentIndex(stream.readLine().toInt());
        outFile.close();
    }
    else if (!outFile.open(QIODevice::ReadOnly))
        ui->statusbar->showMessage("Ошибка чтения файла...");
    ui->statusbar->showMessage(File);
}

void Lamellar::on_Save_menu_triggered()
{
    if (NameFile3 == "" or NameFile3 == " ")
        NameFile3 = QFileDialog::getSaveFileName(this, "Сохранить в файл...", "C:\\Users\\Ivan\\Desktop", "Текстовый документ (*.txt);");
    QFile inFile(NameFile3);
    if (inFile.open(QIODevice::ReadWrite| QIODevice::Text)){
        QTextStream stream(&inFile);
        //Горячий контур
        stream << ui->cBox_material_hot->currentIndex();
        stream << "\n";
        stream << ui->line_hot_T1->text();
        stream << "\n";
        stream << ui->line_hot_T2->text();
        stream << "\n";
        stream << ui->line_hot_pressure->text();
        stream << "\n";
        stream << ui->line_hot_dmass->text();
        stream << "\n";
        stream << ui->cBox_cavity_hot->currentIndex();
        stream << "\n";
        //Холодный контур
        stream << ui->cBox_material_cold->currentIndex();
        stream << "\n";
        stream << ui->line_cold_T1->text();
        stream << "\n";
        stream << ui->line_cold_T2->text();
        stream << "\n";
        stream << ui->line_cold_pressure->text();
        stream << "\n";
        stream << ui->line_cold_dmass->text();
        stream << "\n";
        stream << ui->cBox_cavity_cold->currentIndex();
        stream << "\n";
        //Параметры ТА
        stream << ui->cBox_material_heat_ex->currentIndex();
        stream << "\n";
        stream << ui->line_F_heat->text();
        stream << "\n";
        stream << ui->line_d_eq->text();
        stream << "\n";
        stream << ui->line_F_channel->text();
        stream << "\n";
        stream << ui->line_length_channel->text();
        stream << "\n";
        stream << ui->line_h_gofr->text();
        stream << "\n";
        stream << ui->line_step_gofr->text();
        stream << "\n";
        stream << ui->line_width_channel->text();
        stream << "\n";
        stream << ui->line_gap->text();
        stream << "\n";
        stream << ui->line_delt_wall->text();
        stream << "\n";
        stream << ui->line_length->text();
        stream << "\n";
        stream << ui->line_width->text();
        stream << "\n";
        stream << ui->cBox_current_type->currentIndex();
        inFile.close();
    }
    ui->statusbar->showMessage("Данные сохраненые в файле");
}

void Lamellar::on_Clean_menu_triggered()
{
    //Горячий контур
    ui->line_hot_T1->clear();
    ui->line_hot_T2->clear();
    ui->line_hot_pressure->clear();
    ui->line_hot_dmass->clear();
    //Холодный контур
    ui->line_cold_T1->clear();
    ui->line_cold_T2->clear();
    ui->line_cold_pressure->clear();
    ui->line_cold_dmass->clear();
    //Параметры ТА
    ui->line_F_heat->clear();
    ui->line_d_eq->clear();
    ui->line_F_channel->clear();
    ui->line_length_channel->clear();
    ui->line_h_gofr->clear();
    ui->line_step_gofr->clear();
    ui->line_width_channel->clear();
    ui->line_gap->clear();
    ui->line_delt_wall->clear();
    ui->line_length->clear();
    ui->line_width->clear();

    for(int row = 0; row < 18; row++) //String
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString("").arg(row).arg(1));
        ui->Table->setItem(row, 1, item);
    }
    for(int row = 0; row < 18; row++) //String
    {
        for(int colum = 0; colum < 4; colum++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString("").arg(row).arg(colum));
            ui->TableProperties->setItem(row, colum, item);
        }
    }
    ui->statusbar->showMessage("Поля ввода очищены");
}

void Lamellar::on_Create_menu_triggered()
{
    NameFile3 = QFileDialog::getSaveFileName(this, "Сохранить в файл...", "C:\\Users\\Ivan\\Desktop", "Текстовый документ (*.txt);");
    //Горячий контур
    ui->line_hot_T1->clear();
    ui->line_hot_T2->clear();
    ui->line_hot_pressure->clear();
    ui->line_hot_dmass->clear();
    //Холодный контур
    ui->line_cold_T1->clear();
    ui->line_cold_T2->clear();
    ui->line_cold_pressure->clear();
    ui->line_cold_dmass->clear();
    //Параметры ТА
    ui->line_F_heat->clear();
    ui->line_d_eq->clear();
    ui->line_F_channel->clear();
    ui->line_length_channel->clear();
    ui->line_h_gofr->clear();
    ui->line_step_gofr->clear();
    ui->line_width_channel->clear();
    ui->line_gap->clear();
    ui->line_delt_wall->clear();
    ui->line_length->clear();
    ui->line_width->clear();

    for(int row = 0; row < 18; row++) //String
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString("").arg(row).arg(1));
        ui->Table->setItem(row, 1, item);
    }
    for(int row = 0; row < 18; row++) //String
    {
        for(int colum = 0; colum < 4; colum++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString("").arg(row).arg(colum));
            ui->TableProperties->setItem(row, colum, item);
        }
    }
    ui->statusbar->showMessage("Создан новый файл");
}

void Lamellar::on_Save_as_menu_triggered()
{
    QString File;
    File = QFileDialog::getSaveFileName(this, "Сохранить в файл...", "C:\\Users\\Ivan\\Desktop", "Текстовый документ (*.txt);");
    QFile inFile(File);
    if (inFile.open(QIODevice::ReadWrite| QIODevice::Text)){
        QTextStream stream(&inFile);
        //Горячий контур
        stream << ui->cBox_material_hot->currentIndex();
        stream << "\n";
        stream << ui->line_hot_T1->text();
        stream << "\n";
        stream << ui->line_hot_T2->text();
        stream << "\n";
        stream << ui->line_hot_pressure->text();
        stream << "\n";
        stream << ui->line_hot_dmass->text();
        stream << "\n";
        stream << ui->cBox_cavity_hot->currentIndex();
        stream << "\n";
        //Холодный контур
        stream << ui->cBox_material_cold->currentIndex();
        stream << "\n";
        stream << ui->line_cold_T1->text();
        stream << "\n";
        stream << ui->line_cold_T2->text();
        stream << "\n";
        stream << ui->line_cold_pressure->text();
        stream << "\n";
        stream << ui->line_cold_dmass->text();
        stream << "\n";
        stream << ui->cBox_cavity_cold->currentIndex();
        stream << "\n";
        //Параметры ТА
        stream << ui->cBox_material_heat_ex->currentIndex();
        stream << "\n";
        stream << ui->line_F_heat->text();
        stream << "\n";
        stream << ui->line_d_eq->text();
        stream << "\n";
        stream << ui->line_F_channel->text();
        stream << "\n";
        stream << ui->line_length_channel->text();
        stream << "\n";
        stream << ui->line_h_gofr->text();
        stream << "\n";
        stream << ui->line_step_gofr->text();
        stream << "\n";
        stream << ui->line_width_channel->text();
        stream << "\n";
        stream << ui->line_gap->text();
        stream << "\n";
        stream << ui->line_delt_wall->text();
        stream << "\n";
        stream << ui->line_length->text();
        stream << "\n";
        stream << ui->line_width->text();
        stream << "\n";
        stream << ui->cBox_current_type->currentIndex();
        inFile.close();
    }
}

void Lamellar::on_T_ex_cold_menu_triggered()
{
    if (ui->line_hot_T1->text() != "" &&
        ui->line_hot_T2->text() != "" &&
        ui->line_hot_pressure->text() != "" &&
        ui->line_hot_dmass->text() != "" &&
        ui->line_cold_T1->text() != "" &&
        ui->line_cold_pressure->text() != "" &&
        ui->line_cold_dmass->text() != "")
    {
        ui->statusbar->showMessage("Температура холодного контура на выходе");
        //Запись значений в переменные для расчета
        T1_h = ui->line_hot_T1->text().toDouble();
        T2_h = ui->line_hot_T2->text().toDouble();
        T1_c = ui->line_cold_T1->text().toDouble();
        d_mass_h = ui->line_hot_dmass->text().toDouble();
        d_mass_c = ui->line_cold_dmass->text().toDouble();

        //Перевод значений в размерность
        T1_h = Dimension_T(ui->dimension_T_en_h->currentIndex(), T1_h);
        T2_h = Dimension_T(ui->dimension_T_ex_h->currentIndex(), T2_h);
        T1_c = Dimension_T(ui->dimension_T_en_c->currentIndex(), T1_c);
        d_mass_h = Dimension_dmass(ui->dimension_m_h->currentIndex(), d_mass_h);
        d_mass_c = Dimension_dmass(ui->dimension_m_c->currentIndex(), d_mass_c);

        switch (ui->cBox_material_hot->currentIndex()) {
        case 0:
            density_hot = 995.7/(0.984 + 0.483e-3 * T_medium(T1_h, T2_h));
            heat_capacity_hot = 4194.0 - 1.15 * T_medium(T1_h, T2_h) + 1.5e-2 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h);
            thermal_conductivity_hot = 0.553 * (1 + 0.003 * T_medium(T1_h, T2_h));
            kinem_coef_hot = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_h, T2_h)) + 221e-6 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h));
            dinamic_coef_hot = kinem_coef_hot * density_hot;
            thermal_coef_hot = 0.132e-6 * (1 + 0.003 * T_medium(T1_h, T2_h));
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 1:
            density_hot = P_h * 1000/(287.4 * (T_medium(T1_h, T2_h) + 273.15));
            heat_capacity_hot = (1.0005 + 1.1904e-4 * (T_medium(T1_h, T2_h)))*1000;
            thermal_conductivity_hot = 2.44e-2 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.82);
            dinamic_coef_hot = 1.717e-5 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.683);
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 2:
            density_hot = 4.364e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 3.398e-3 * T_medium(T1_h, T2_h) + 1.219;
            heat_capacity_hot = 3.814e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 0.021e-3 * T_medium(T1_h, T2_h) + 1041;
            thermal_conductivity_hot = -3.77e-8 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 7.5e-5 * T_medium(T1_h, T2_h) + 0.024;
            dinamic_coef_hot = -2.29e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.56e-8 * T_medium(T1_h, T2_h) + 1.66e-5;
            kinem_coef_hot = 8.223e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 9.09e-8 * T_medium(T1_h, T2_h) + 1.336e-5;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 3:
            density_hot = 8.969e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 5.837e-3 * T_medium(T1_h, T2_h) + 1.922;
            heat_capacity_hot = -7.685e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 1.04e-3 * T_medium(T1_h, T2_h) + 823.4;
            thermal_conductivity_hot = (2.733e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.072 * T_medium(T1_h, T2_h) + 14.681)*10e-4;
            dinamic_coef_hot = 1.98e-12 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.067e-8 * T_medium(T1_h, T2_h) + 1.376e-5;
            kinem_coef_hot = (7.904e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.047 * T_medium(T1_h, T2_h) + 7.054)*10e-7;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 4:
            density_hot = 1016;
            heat_capacity_hot = 2'002;
                thermal_conductivity_hot = 0.586;
            dinamic_coef_hot = 0.826e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 5:
            density_hot = 1040;
            heat_capacity_hot = 1'915;
                thermal_conductivity_hot = 0.540;
            dinamic_coef_hot = 1.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 6:
            density_hot = 1073;
            heat_capacity_hot = 1'830;
                thermal_conductivity_hot = 0.502;
            dinamic_coef_hot = 1.46e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 7:
            density_hot = 1089;
            heat_capacity_hot = 1'774;
                thermal_conductivity_hot = 0.460;
            dinamic_coef_hot = 2.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 8:
            density_hot = 1115;
            heat_capacity_hot = 1'659;
                thermal_conductivity_hot = 0.423;
            dinamic_coef_hot = 3.1e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 9:
            density_hot = 1142;
            heat_capacity_hot = 1'573;
                thermal_conductivity_hot = 0.385;
            dinamic_coef_hot = 5.08e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 10:
            density_hot = 1169;
            heat_capacity_hot = 1'487;
                thermal_conductivity_hot = 0.356;
            dinamic_coef_hot = 9.4e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        }
        //Выбор материала охлаждающего контура для расчета холодной части
        switch (ui->cBox_material_cold->currentIndex()) {
        case 0:
            density_cold = 995.7/(0.984 + 0.483e-3 * T_medium(T1_c, T2_c));
            heat_capacity_cold = 4194.0 - 1.15 * T_medium(T1_c, T2_c) + 1.5e-2 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c);
            thermal_conductivity_cold = 0.553 * (1 + 0.003 * T_medium(T1_c, T2_c));
            kinem_coef_cold = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_c, T2_c)) + 221e-6 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c));
            dinamic_coef_cold = kinem_coef_cold * density_cold;
            thermal_coef_cold = 0.132e-6 * (1 + 0.003 * T_medium(T1_c, T2_c));
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 1:
            density_cold = P_c * 1000/(287.4 * (T_medium(T1_c, T2_c) + 273.15));
            heat_capacity_cold = (1.0005 + 1.1904e-4 * (T_medium(T1_c, T2_c)))*1000;
            thermal_conductivity_cold = 2.44e-2 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.82);
            dinamic_coef_cold = 1.717e-5 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.683);
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 2:
            density_cold = 4.364e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 3.398e-3 * T_medium(T1_c, T2_c) + 1.219;
            heat_capacity_cold = 3.814e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 0.021e-3 * T_medium(T1_c, T2_c) + 1041;
            thermal_conductivity_cold = -3.77e-8 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 7.5e-5 * T_medium(T1_c, T2_c) + 0.024;
            dinamic_coef_cold =  -2.29e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.56e-8 * T_medium(T1_c, T2_c) + 1.66e-5;
            kinem_coef_cold = 8.223e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 9.09e-8 * T_medium(T1_c, T2_c) + 1.336e-5;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 3:
            density_cold = 8.969e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 5.837e-3 * T_medium(T1_c, T2_c) + 1.922;
            heat_capacity_cold = -7.685e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 1.04e-3 * T_medium(T1_c, T2_c) + 823.4;
            thermal_conductivity_cold = (2.733e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.072 * T_medium(T1_c, T2_c) + 14.681)*10e-4;
            dinamic_coef_cold = 1.98e-12 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.067e-8 * T_medium(T1_c, T2_c) + 1.376e-5;
            kinem_coef_cold = (7.904e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.047 * T_medium(T1_c, T2_c) + 7.054)*10e-7;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 4:
            density_cold = 1016;
            heat_capacity_cold = 2'002;
                thermal_conductivity_cold = 0.586;
            dinamic_coef_cold = 0.826e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 5:
            density_cold = 1040;
            heat_capacity_cold = 1'915;
                thermal_conductivity_cold = 0.540;
            dinamic_coef_cold = 1.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 6:
            density_cold = 1073;
            heat_capacity_cold = 1'830;
                thermal_conductivity_cold = 0.502;
            dinamic_coef_cold = 1.46e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 7:
            density_cold = 1089;
            heat_capacity_cold = 1'774;
                thermal_conductivity_cold = 0.460;
            dinamic_coef_cold = 2.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 8:
            density_cold = 1115;
            heat_capacity_cold = 1'659;
                thermal_conductivity_cold = 0.423;
            dinamic_coef_cold = 3.1e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 9:
            density_cold = 1142;
            heat_capacity_cold = 1'573;
                thermal_conductivity_cold = 0.385;
            dinamic_coef_cold = 5.08e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 10:
            density_cold = 1169;
            heat_capacity_cold = 1'487;
                thermal_conductivity_cold = 0.356;
            dinamic_coef_cold = 9.4e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        }

        T2_c = (heat_capacity_hot*d_mass_h*(T1_h - T2_h) + heat_capacity_cold*d_mass_c*T1_c) / (heat_capacity_cold*d_mass_c);
        ui->line_cold_T2->setText(QString::number(T2_c, 'f', 4));
    }
    else
        ui->statusbar->showMessage("Введите данные для выполнения расчета...");
}

void Lamellar::on_T_ex_hot_menu_triggered()
{
    if (ui->line_hot_T1->text() != "" &&
        ui->line_hot_pressure->text() != "" &&
        ui->line_hot_dmass->text() != "" &&
        ui->line_cold_T1->text() != "" &&
        ui->line_cold_T2->text() != "" &&
        ui->line_cold_pressure->text() != "" &&
        ui->line_cold_dmass->text() != "")
    {
        ui->statusbar->showMessage("Температура горячего контура на выходе");
        //Запись значений в переменные для расчета
        T1_h = ui->line_hot_T1->text().toDouble();
        T1_c = ui->line_cold_T1->text().toDouble();
        T2_c = ui->line_cold_T2->text().toDouble();
        d_mass_h = ui->line_hot_dmass->text().toDouble();
        d_mass_c = ui->line_cold_dmass->text().toDouble();

        //Перевод значений в размерность
        T1_h = Dimension_T(ui->dimension_T_en_h->currentIndex(), T1_h);
        T1_c = Dimension_T(ui->dimension_T_en_c->currentIndex(), T1_c);
        T2_c = Dimension_T(ui->dimension_T_ex_c->currentIndex(), T2_c);
        d_mass_h = Dimension_dmass(ui->dimension_m_h->currentIndex(), d_mass_h);
        d_mass_c = Dimension_dmass(ui->dimension_m_c->currentIndex(), d_mass_c);

        switch (ui->cBox_material_hot->currentIndex()) {
        case 0:
            density_hot = 995.7/(0.984 + 0.483e-3 * T_medium(T1_h, T2_h));
            heat_capacity_hot = 4194.0 - 1.15 * T_medium(T1_h, T2_h) + 1.5e-2 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h);
            thermal_conductivity_hot = 0.553 * (1 + 0.003 * T_medium(T1_h, T2_h));
            kinem_coef_hot = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_h, T2_h)) + 221e-6 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h));
            dinamic_coef_hot = kinem_coef_hot * density_hot;
            thermal_coef_hot = 0.132e-6 * (1 + 0.003 * T_medium(T1_h, T2_h));
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 1:
            density_hot = P_h * 1000/(287.4 * (T_medium(T1_h, T2_h) + 273.15));
            heat_capacity_hot = (1.0005 + 1.1904e-4 * (T_medium(T1_h, T2_h)))*1000;
            thermal_conductivity_hot = 2.44e-2 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.82);
            dinamic_coef_hot = 1.717e-5 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.683);
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 2:
            density_hot = 4.364e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 3.398e-3 * T_medium(T1_h, T2_h) + 1.219;
            heat_capacity_hot = 3.814e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 0.021e-3 * T_medium(T1_h, T2_h) + 1041;
            thermal_conductivity_hot = -3.77e-8 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 7.5e-5 * T_medium(T1_h, T2_h) + 0.024;
            dinamic_coef_hot = -2.29e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.56e-8 * T_medium(T1_h, T2_h) + 1.66e-5;
            kinem_coef_hot = 8.223e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 9.09e-8 * T_medium(T1_h, T2_h) + 1.336e-5;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 3:
            density_hot = 8.969e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 5.837e-3 * T_medium(T1_h, T2_h) + 1.922;
            heat_capacity_hot = -7.685e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 1.04e-3 * T_medium(T1_h, T2_h) + 823.4;
            thermal_conductivity_hot = (2.733e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.072 * T_medium(T1_h, T2_h) + 14.681)*10e-4;
            dinamic_coef_hot = 1.98e-12 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.067e-8 * T_medium(T1_h, T2_h) + 1.376e-5;
            kinem_coef_hot = (7.904e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.047 * T_medium(T1_h, T2_h) + 7.054)*10e-7;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 4:
            density_hot = 1016;
            heat_capacity_hot = 2'002;
                thermal_conductivity_hot = 0.586;
            dinamic_coef_hot = 0.826e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 5:
            density_hot = 1040;
            heat_capacity_hot = 1'915;
                thermal_conductivity_hot = 0.540;
            dinamic_coef_hot = 1.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 6:
            density_hot = 1073;
            heat_capacity_hot = 1'830;
                thermal_conductivity_hot = 0.502;
            dinamic_coef_hot = 1.46e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 7:
            density_hot = 1089;
            heat_capacity_hot = 1'774;
                thermal_conductivity_hot = 0.460;
            dinamic_coef_hot = 2.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 8:
            density_hot = 1115;
            heat_capacity_hot = 1'659;
                thermal_conductivity_hot = 0.423;
            dinamic_coef_hot = 3.1e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 9:
            density_hot = 1142;
            heat_capacity_hot = 1'573;
                thermal_conductivity_hot = 0.385;
            dinamic_coef_hot = 5.08e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 10:
            density_hot = 1169;
            heat_capacity_hot = 1'487;
                thermal_conductivity_hot = 0.356;
            dinamic_coef_hot = 9.4e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        }
        //Выбор материала охлаждающего контура для расчета холодной части
        switch (ui->cBox_material_cold->currentIndex()) {
        case 0:
            density_cold = 995.7/(0.984 + 0.483e-3 * T_medium(T1_c, T2_c));
            heat_capacity_cold = 4194.0 - 1.15 * T_medium(T1_c, T2_c) + 1.5e-2 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c);
            thermal_conductivity_cold = 0.553 * (1 + 0.003 * T_medium(T1_c, T2_c));
            kinem_coef_cold = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_c, T2_c)) + 221e-6 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c));
            dinamic_coef_cold = kinem_coef_cold * density_cold;
            thermal_coef_cold = 0.132e-6 * (1 + 0.003 * T_medium(T1_c, T2_c));
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 1:
            density_cold = P_c * 1000/(287.4 * (T_medium(T1_c, T2_c) + 273.15));
            heat_capacity_cold = (1.0005 + 1.1904e-4 * (T_medium(T1_c, T2_c)))*1000;
            thermal_conductivity_cold = 2.44e-2 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.82);
            dinamic_coef_cold = 1.717e-5 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.683);
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 2:
            density_cold = 4.364e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 3.398e-3 * T_medium(T1_c, T2_c) + 1.219;
            heat_capacity_cold = 3.814e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 0.021e-3 * T_medium(T1_c, T2_c) + 1041;
            thermal_conductivity_cold = -3.77e-8 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 7.5e-5 * T_medium(T1_c, T2_c) + 0.024;
            dinamic_coef_cold =  -2.29e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.56e-8 * T_medium(T1_c, T2_c) + 1.66e-5;
            kinem_coef_cold = 8.223e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 9.09e-8 * T_medium(T1_c, T2_c) + 1.336e-5;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 3:
            density_cold = 8.969e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 5.837e-3 * T_medium(T1_c, T2_c) + 1.922;
            heat_capacity_cold = -7.685e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 1.04e-3 * T_medium(T1_c, T2_c) + 823.4;
            thermal_conductivity_cold = (2.733e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.072 * T_medium(T1_c, T2_c) + 14.681)*10e-4;
            dinamic_coef_cold = 1.98e-12 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.067e-8 * T_medium(T1_c, T2_c) + 1.376e-5;
            kinem_coef_cold = (7.904e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.047 * T_medium(T1_c, T2_c) + 7.054)*10e-7;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 4:
            density_cold = 1016;
            heat_capacity_cold = 2'002;
                thermal_conductivity_cold = 0.586;
            dinamic_coef_cold = 0.826e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 5:
            density_cold = 1040;
            heat_capacity_cold = 1'915;
                thermal_conductivity_cold = 0.540;
            dinamic_coef_cold = 1.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 6:
            density_cold = 1073;
            heat_capacity_cold = 1'830;
                thermal_conductivity_cold = 0.502;
            dinamic_coef_cold = 1.46e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 7:
            density_cold = 1089;
            heat_capacity_cold = 1'774;
                thermal_conductivity_cold = 0.460;
            dinamic_coef_cold = 2.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 8:
            density_cold = 1115;
            heat_capacity_cold = 1'659;
                thermal_conductivity_cold = 0.423;
            dinamic_coef_cold = 3.1e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 9:
            density_cold = 1142;
            heat_capacity_cold = 1'573;
                thermal_conductivity_cold = 0.385;
            dinamic_coef_cold = 5.08e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 10:
            density_cold = 1169;
            heat_capacity_cold = 1'487;
                thermal_conductivity_cold = 0.356;
            dinamic_coef_cold = 9.4e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        }

        T2_h = (heat_capacity_hot*d_mass_h*T1_h - heat_capacity_cold*d_mass_c*(T2_c - T1_c)) / (heat_capacity_hot*d_mass_h);
        ui->line_hot_T2->setText(QString::number(T2_h, 'f', 4));
    }
    else
        ui->statusbar->showMessage("Введите данные для выполнения расчета...");
}

void Lamellar::on_Cheak_menu_triggered()
{
    if (ui->line_hot_T1->text() != "" &&
        ui->line_hot_T2->text() != "" &&
        ui->line_hot_pressure->text() != "" &&
        ui->line_hot_dmass->text() != "" &&
        ui->line_cold_T1->text() != "" &&
        ui->line_cold_pressure->text() != "" &&
        ui->line_cold_dmass->text() != "" &&
        ui->line_F_heat->text() != "" &&
        ui->line_d_eq->text() != "" &&
        ui->line_F_channel->text() != "" &&
        ui->line_length_channel->text() != "" &&
        ui->line_h_gofr->text() != "" &&
        ui->line_step_gofr->text() != "" &&
        ui->line_width_channel->text() != "" &&
        ui->line_gap->text() != "" &&
        ui->line_delt_wall->text() != "" &&
        ui->line_length->text() != "" &&
        ui->line_width->text() != "")
    {
        //Запись значений в переменные для расчета
        T1_h = ui->line_hot_T1->text().toDouble();
        T2_h = ui->line_hot_T2->text().toDouble();
        T1_c = ui->line_cold_T1->text().toDouble();
        T2_c = ui->line_cold_T2->text().toDouble();
        d_mass_h = ui->line_hot_dmass->text().toDouble();
        d_mass_c = ui->line_cold_dmass->text().toDouble();

        //Перевод значений в размерность
        T1_h = Dimension_T(ui->dimension_T_en_h->currentIndex(), T1_h);
        T2_h = Dimension_T(ui->dimension_T_ex_h->currentIndex(), T2_h);
        T1_c = Dimension_T(ui->dimension_T_en_c->currentIndex(), T1_c);
        T2_c = Dimension_T(ui->dimension_T_en_c->currentIndex(), T1_c);
        d_mass_h = Dimension_dmass(ui->dimension_m_h->currentIndex(), d_mass_h);
        d_mass_c = Dimension_dmass(ui->dimension_m_c->currentIndex(), d_mass_c);

        switch (ui->cBox_material_hot->currentIndex()) {
        case 0:
            density_hot = 995.7/(0.984 + 0.483e-3 * T_medium(T1_h, T2_h));
            heat_capacity_hot = 4194.0 - 1.15 * T_medium(T1_h, T2_h) + 1.5e-2 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h);
            thermal_conductivity_hot = 0.553 * (1 + 0.003 * T_medium(T1_h, T2_h));
            kinem_coef_hot = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_h, T2_h)) + 221e-6 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h));
            dinamic_coef_hot = kinem_coef_hot * density_hot;
            thermal_coef_hot = 0.132e-6 * (1 + 0.003 * T_medium(T1_h, T2_h));
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            //Проверка правильности ввода температур для воды
            if (T1_c < 0 || T1_c > 100){
                ui->statusbar->showMessage("Ошибка: Холодный контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T2_c < 0 || T2_c > 100){
                ui->statusbar->showMessage("Ошибка: Холодный контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T1_h < 0 || T1_h > 100){
                ui->statusbar->showMessage("Ошибка: Горячий контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T2_h < 0 || T2_h > 100){
                ui->statusbar->showMessage("Ошибка: Горячий контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            break;
        case 1:
            density_hot = P_h * 1000/(287.4 * (T_medium(T1_h, T2_h) + 273.15));
            heat_capacity_hot = (1.0005 + 1.1904e-4 * (T_medium(T1_h, T2_h)))*1000;
            thermal_conductivity_hot = 2.44e-2 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.82);
            dinamic_coef_hot = 1.717e-5 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.683);
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 2:
            density_hot = 4.364e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 3.398e-3 * T_medium(T1_h, T2_h) + 1.219;
            heat_capacity_hot = 3.814e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 0.021e-3 * T_medium(T1_h, T2_h) + 1041;
            thermal_conductivity_hot = -3.77e-8 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 7.5e-5 * T_medium(T1_h, T2_h) + 0.024;
            dinamic_coef_hot = -2.29e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.56e-8 * T_medium(T1_h, T2_h) + 1.66e-5;
            kinem_coef_hot = 8.223e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 9.09e-8 * T_medium(T1_h, T2_h) + 1.336e-5;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 3:
            density_hot = 8.969e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 5.837e-3 * T_medium(T1_h, T2_h) + 1.922;
            heat_capacity_hot = -7.685e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 1.04e-3 * T_medium(T1_h, T2_h) + 823.4;
            thermal_conductivity_hot = (2.733e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.072 * T_medium(T1_h, T2_h) + 14.681)*10e-4;
            dinamic_coef_hot = 1.98e-12 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.067e-8 * T_medium(T1_h, T2_h) + 1.376e-5;
            kinem_coef_hot = (7.904e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.047 * T_medium(T1_h, T2_h) + 7.054)*10e-7;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 4:
            density_hot = 1.040;
            heat_capacity_hot = 1915;
            thermal_conductivity_hot = 0.540;
            dinamic_coef_hot = 1.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        }
        //Выбор материала охлаждающего контура для расчета холодной части
        switch (ui->cBox_material_cold->currentIndex()) {
        case 0:
            density_cold = 995.7/(0.984 + 0.483e-3 * T_medium(T1_c, T2_c));
            heat_capacity_cold = 4194.0 - 1.15 * T_medium(T1_c, T2_c) + 1.5e-2 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c);
            thermal_conductivity_cold = 0.553 * (1 + 0.003 * T_medium(T1_c, T2_c));
            kinem_coef_cold = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_c, T2_c)) + 221e-6 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c));
            dinamic_coef_cold = kinem_coef_cold * density_cold;
            thermal_coef_cold = 0.132e-6 * (1 + 0.003 * T_medium(T1_c, T2_c));
            //Проверка правильности ввода температур для воды
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            if (T1_c < 0 || T1_c > 100){
                ui->statusbar->showMessage("Ошибка: Холодный контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T2_c < 0 || T2_c > 100){
                ui->statusbar->showMessage("Ошибка: Холодный контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T1_h < 0 || T1_h > 100){
                ui->statusbar->showMessage("Ошибка: Горячий контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            if (T2_h < 0 || T2_h > 100){
                ui->statusbar->showMessage("Ошибка: Горячий контур при данной температуре претерпевает фазовый переход! Откорректируйте температуры...");
                return;
            }
            break;
        case 1:
            density_cold = P_c * 1000/(287.4 * (T_medium(T1_c, T2_c) + 273.15));
            heat_capacity_cold = (1.0005 + 1.1904e-4 * (T_medium(T1_c, T2_c)))*1000;
            thermal_conductivity_cold = 2.44e-2 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.82);
            dinamic_coef_cold = 1.717e-5 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.683);
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 2:
            density_cold = 4.364e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 3.398e-3 * T_medium(T1_c, T2_c) + 1.219;
            heat_capacity_cold = 3.814e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 0.021e-3 * T_medium(T1_c, T2_c) + 1041;
            thermal_conductivity_cold = -3.77e-8 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 7.5e-5 * T_medium(T1_c, T2_c) + 0.024;
            dinamic_coef_cold =  -2.29e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.56e-8 * T_medium(T1_c, T2_c) + 1.66e-5;
            kinem_coef_cold = 8.223e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 9.09e-8 * T_medium(T1_c, T2_c) + 1.336e-5;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 3:
            density_cold = 8.969e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 5.837e-3 * T_medium(T1_c, T2_c) + 1.922;
            heat_capacity_cold = -7.685e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 1.04e-3 * T_medium(T1_c, T2_c) + 823.4;
            thermal_conductivity_cold = (2.733e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.072 * T_medium(T1_c, T2_c) + 14.681)*10e-4;
            dinamic_coef_cold = 1.98e-12 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.067e-8 * T_medium(T1_c, T2_c) + 1.376e-5;
            kinem_coef_cold = (7.904e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.047 * T_medium(T1_c, T2_c) + 7.054)*10e-7;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 4:
            density_cold = 1.040;
            heat_capacity_cold = 1915;
            thermal_conductivity_cold = 0.540;
            dinamic_coef_cold = 1.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        }
        //Проверка правильности ввода температур
        if (T1_h < T2_h){
            ui->statusbar->showMessage("Ошибка: Горячий контур должен остывать! Откорректируйте температуры...");
            return;
        }
        if (T2_c < T1_c){
            ui->statusbar->showMessage("Ошибка: Холодный контур должен нагреваться! Откорректируйте температуры...");
            return;
        }
        //Проверка закона сохранения энергии
        double Power_h, Power_c;
        Power_h = Power(T1_h, T2_h, d_mass_h, heat_capacity_hot);
        Power_c = Power(T1_c, T2_c, d_mass_c, heat_capacity_cold);
        if (Power_h <= Power_c * 0.9)
        {
            ui->statusbar->showMessage("Ошибка: не выполняется закон сохранения энергии! Откорректируйте температуры...");
            return;
        }
        else if(Power_h >= Power_c * 1.1)
        {
            ui->statusbar->showMessage("Ошибка: не выполняется закон сохранения энергии! Откорректируйте температуры...");
            return;
        }
        else
            ui->statusbar->showMessage("Проверка: Введенные данные корректны");
    }
    else{
        ui->statusbar->showMessage("Введите данные для выполнения расчета...");
        return;
    }
}

//////////////////////////////////////Кнопки////////////////////////////////////////

void Lamellar::on_Button_Exit_clicked()
{
    QApplication::quit();
}

void Lamellar::on_Button_clear_table_clicked()
{
    for(int row = 0; row < 18; row++) //String
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString("").arg(row).arg(1));
        ui->Table->setItem(row, 1, item);
    }
    for(int row = 0; row < 20; row++) //String
    {
        for(int colum = 0; colum < 4; colum++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString("").arg(row).arg(colum));
            ui->TableProperties->setItem(row, colum, item);
        }
    }
    ui->statusbar->showMessage("Таблицы очищены");
}

void Lamellar::on_Button_save_exel_clicked() //Переделать область сохранения!
{
    try {
        QString NameExcel;
        NameExcel = QFileDialog::getSaveFileName(this, "Сохранить в файл...", "C:\\Users\\Ivan\\Desktop", "(*.xlsx);");
        NameExcel.replace(R"(/)", R"(\)");

        QAxObject* excel     = new QAxObject("Excel.Application");
        excel->setProperty("Visible", false);
        excel->setProperty("DisplayAlerts", "0");
        QAxObject* workbooks = excel->querySubObject("Workbooks");
        QAxObject* workbook  = workbooks->querySubObject("Add");
        QAxObject* sheets    = workbook->querySubObject("Worksheets");
        QAxObject* sheet     = sheets->querySubObject("Item(int)",1);

        //Запись в файл решения 2...5:2...20
        QAxObject* Solution = sheet->querySubObject("Cells(int, int)", 1, 3);
        Solution->dynamicCall("SetValue(const QVariant&)", "Решение");
        QAxObject* paramSolution = sheet->querySubObject("Cells(int, int)", 2, 2);
        paramSolution->dynamicCall("SetValue(const QVariant&)", "Параметр");
        QAxObject* valuesSolution = sheet->querySubObject("Cells(int, int)", 2, 3);
        valuesSolution->dynamicCall("SetValue(const QVariant&)", "Величина");
        QAxObject* dimensionSolution = sheet->querySubObject("Cells(int, int)", 2, 4);
        dimensionSolution->dynamicCall("SetValue(const QVariant&)", "Размерность");
        QAxObject* noteSolution = sheet->querySubObject("Cells(int, int)", 2, 5);
        noteSolution->dynamicCall("SetValue(const QVariant&)", "Примечание");

        for (int row = 1; row < 18; row++){
            QStringList dataRow;
            for (int colum = 1; colum < 2; colum++){
                QAxObject* cell = sheet->querySubObject("Cells(int, int)", row+2, colum);
                QVariant value = cell->dynamicCall("SetValue(const QVariant&)", QString::number(row));
                dataRow.append(value.toString());
            }
        }

        for(int i=0; i<=18; i++)    //Строки
        {
            QStringList dataRow;
            QAxObject* cell = sheet->querySubObject("Cells(int, int)", i+2, 1);
            QVariant value = cell->dynamicCall("SetValue(const QVariant&)", QString::number(i));
            dataRow.append(value.toString());

            for(int j=0; j<=4; j++) //Столбцы
            {
                QVariant Value = ui->Table->model()->data(ui->Table->model()->index(i,j)); //i  - начать с 2 ячейки j - упустить первый столбец
                QAxObject* cell = sheet->querySubObject("Cells(QVariant,QVariant)", i+3, j+2);
                //Вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                cell->setProperty("Value", QVariant(Value));
            }
        }

        //Запись в файл теплофизических свойст 7...9:2...22
        QAxObject* Properties = sheet->querySubObject("Cells(int, int)", 1, 7);
        Properties->dynamicCall("SetValue(const QVariant&)", "Теплофизические свойства вещест");
        QAxObject* paramProperties = sheet->querySubObject("Cells(int, int)", 2, 7);
        paramProperties->dynamicCall("SetValue(const QVariant&)", "Параметр");
        QAxObject* valuesProperties = sheet->querySubObject("Cells(int, int)", 2, 8);
        valuesProperties->dynamicCall("SetValue(const QVariant&)", "Величина");
        QAxObject* dimensionProperties = sheet->querySubObject("Cells(int, int)", 2, 9);
        dimensionProperties->dynamicCall("SetValue(const QVariant&)", "Размерность");

        for(int i=0; i<=20; i++)
        {
            for(int j=0; j<=3; j++)
            {
                QVariant Value = ui->TableProperties->model()->data(ui->Table->model()->index(i,j)); //i  - начать с 2 ячейки j - упустить первый столбец
                QAxObject* cell = sheet->querySubObject("Cells(QVariant,QVariant)", i+3, j+7);
                //Вставка значения переменной data (любой тип, приводимый к QVariant) в полученную ячейку
                cell->setProperty("Value", QVariant(Value));
            }
        }

        workbook->dynamicCall("SaveAs(NameExcel&)", NameExcel);
        workbook->dynamicCall("Close (Boolean)", false);
        excel->dynamicCall("Quit(void)");

        delete workbook;
        delete workbooks;
        delete excel;
        ui->statusbar->showMessage("Результаты решения успешно сохранены");
    }
    catch (...) {
        ui->statusbar->showMessage("Произошла ошибка! Данные не сохранены");
    }
}

void Lamellar::on_Button_Start_clicked()
{
    if (ui->line_hot_T1->text() != "" &&
        ui->line_hot_T2->text() != "" &&
        ui->line_hot_pressure->text() != "" &&
        ui->line_hot_dmass->text() != "" &&
        ui->line_cold_T1->text() != "" &&
        ui->line_cold_pressure->text() != "" &&
        ui->line_cold_dmass->text() != "" &&
        ui->line_F_heat->text() != "" &&
        ui->line_d_eq->text() != "" &&
        ui->line_F_channel->text() != "" &&
        ui->line_length_channel->text() != "" &&
        ui->line_h_gofr->text() != "" &&
        ui->line_step_gofr->text() != "" &&
        ui->line_width_channel->text() != "" &&
        ui->line_gap->text() != "" &&
        ui->line_delt_wall->text() != "" &&
        ui->line_length->text() != "" &&
        ui->line_width->text() != "")
    {
        QTableWidgetItem *item = new QTableWidgetItem();

        //Запись значений в переменные для расчета
        T1_h = ui->line_hot_T1->text().toDouble();
        T2_h = ui->line_hot_T2->text().toDouble();
        T1_c = ui->line_cold_T1->text().toDouble();
        T2_c = ui->line_cold_T2->text().toDouble();
        d_mass_h = ui->line_hot_dmass->text().toDouble();
        d_mass_c = ui->line_cold_dmass->text().toDouble();
        P_h = ui->line_hot_pressure->text().toDouble();
        P_c = ui->line_cold_pressure->text().toDouble();



        //Перевод значений в размерность
        T1_h = Dimension_T(ui->dimension_T_en_h->currentIndex(), T1_h);
        T2_h = Dimension_T(ui->dimension_T_ex_h->currentIndex(), T2_h);
        T1_c = Dimension_T(ui->dimension_T_en_c->currentIndex(), T1_c);
        T2_c = Dimension_T(ui->dimension_T_ex_c->currentIndex(), T2_c);
        d_mass_h = Dimension_dmass(ui->dimension_m_h->currentIndex(), d_mass_h);
        d_mass_c = Dimension_dmass(ui->dimension_m_c->currentIndex(), d_mass_c);
        P_h = Dimension_P(ui->dimension_P_h->currentIndex(), P_h);
        P_c = Dimension_P(ui->dimension_P_c->currentIndex(), P_c);


        //Выбор матриала охлаждаемого контура для расчета горячей части
        switch (ui->cBox_material_hot->currentIndex()) {
        case 0:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Вода"));
            density_hot = 995.7/(0.984 + 0.483e-3 * T_medium(T1_h, T2_h));
            heat_capacity_hot = 4194.0 - 1.15 * T_medium(T1_h, T2_h) + 1.5e-2 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h);
            thermal_conductivity_hot = 0.553 * (1 + 0.003 * T_medium(T1_h, T2_h));
            kinem_coef_hot = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_h, T2_h)) + 221e-6 * T_medium(T1_h, T2_h)*T_medium(T1_h, T2_h));
            dinamic_coef_hot = kinem_coef_hot * density_hot;
            thermal_coef_hot = 0.132e-6 * (1 + 0.003 * T_medium(T1_h, T2_h));
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 1:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Воздух"));
            density_hot = P_h * 1000/(287.4 * (T_medium(T1_h, T2_h) + 273.15));
            heat_capacity_hot = (1.0005 + 1.1904e-4 * (T_medium(T1_h, T2_h)))*1000;
            thermal_conductivity_hot = 2.44e-2 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.82);
            dinamic_coef_hot = 1.717e-5 * qPow(((T_medium(T1_h, T2_h) + 273.15)/273.15), 0.683);
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 2:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Азот"));
            density_hot = 4.364e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 3.398e-3 * T_medium(T1_h, T2_h) + 1.219;
            heat_capacity_hot = 3.814e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 0.021e-3 * T_medium(T1_h, T2_h) + 1041;
            thermal_conductivity_hot = -3.77e-8 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 7.5e-5 * T_medium(T1_h, T2_h) + 0.024;
            dinamic_coef_hot = -2.29e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.56e-8 * T_medium(T1_h, T2_h) + 1.66e-5;
            kinem_coef_hot = 8.223e-11 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 9.09e-8 * T_medium(T1_h, T2_h) + 1.336e-5;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 3:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Диоксид углерода"));
            density_hot = 8.969e-6 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) - 5.837e-3 * T_medium(T1_h, T2_h) + 1.922;
            heat_capacity_hot = -7.685e-4 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 1.04e-3 * T_medium(T1_h, T2_h) + 823.4;
            thermal_conductivity_hot = (2.733e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.072 * T_medium(T1_h, T2_h) + 14.681)*10e-4;
            dinamic_coef_hot = 1.98e-12 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 4.067e-8 * T_medium(T1_h, T2_h) + 1.376e-5;
            kinem_coef_hot = (7.904e-5 * T_medium(T1_h, T2_h) * T_medium(T1_h, T2_h) + 0.047 * T_medium(T1_h, T2_h) + 7.054)*10e-7;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 4:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 10%"));
            density_hot = 1016;
            heat_capacity_hot = 2'002;
                thermal_conductivity_hot = 0.586;
            dinamic_coef_hot = 0.826e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 5:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 20%"));
            density_hot = 1040;
            heat_capacity_hot = 1'915;
                thermal_conductivity_hot = 0.540;
            dinamic_coef_hot = 1.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 6:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 30%"));
            density_hot = 1073;
            heat_capacity_hot = 1'830;
                thermal_conductivity_hot = 0.502;
            dinamic_coef_hot = 1.46e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 7:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 40%"));
            density_hot = 1089;
            heat_capacity_hot = 1'774;
                thermal_conductivity_hot = 0.460;
            dinamic_coef_hot = 2.07e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 8:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 50%"));
            density_hot = 1115;
            heat_capacity_hot = 1'659;
                thermal_conductivity_hot = 0.423;
            dinamic_coef_hot = 3.1e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 9:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 60%"));
            density_hot = 1142;
            heat_capacity_hot = 1'573;
                thermal_conductivity_hot = 0.385;
            dinamic_coef_hot = 5.08e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        case 10:
            ui->TableProperties->setItem(0, 0, new QTableWidgetItem("Раствор глицерина 70%"));
            density_hot = 1169;
            heat_capacity_hot = 1'487;
                thermal_conductivity_hot = 0.356;
            dinamic_coef_hot = 9.4e-3;
            kinem_coef_hot = dinamic_coef_hot / density_hot;
            thermal_coef_hot = thermal_conductivity_hot / (heat_capacity_hot * density_hot);
            Prantdl_hot = kinem_coef_hot / thermal_coef_hot;
            break;
        }
        //Вывод теплофизических параметров охлаждаемого контура в консоль
        {
            double Data[7];
            QString dimension[7] = {"кг/м3", "Дж/(кг К)", "Вт/(м К)", "Па с", "м2/с", "м2/с", ""};
            QString parameter[7] = {"Плотность", "Теплоемкость", "Теплопроводность", "Динамическая вязкость", "Кинематическая вязкость", "Температуропроводность", "Число Прандтля"};
            Data[0] = density_hot;
            Data[1] = heat_capacity_hot;
            Data[2] = thermal_conductivity_hot;
            Data[3] = dinamic_coef_hot;
            Data[4] = kinem_coef_hot;
            Data[5] = thermal_coef_hot;
            Data[6] = Prantdl_hot;
            ui->TableProperties->horizontalHeader()->resizeSection(0,110);
            ui->TableProperties->horizontalHeader()->resizeSection(1,90);
            ui->TableProperties->horizontalHeader()->resizeSection(2,90);
            ui->TableProperties->setSpan(0,0,1,3);
            for(int row = 1; row < 8; row++) //String
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString(QString::number(Data[row-1], 'f', 8)).arg(row).arg(1));
                ui->TableProperties->setItem(row, 1, item);
                ui->TableProperties->setItem(row, 2, new QTableWidgetItem(dimension[row-1]));
                ui->TableProperties->setItem(row, 0, new QTableWidgetItem(parameter[row-1]));
            }
        }

        //Выбор материала охлаждающего контура для расчета холодной части
        switch (ui->cBox_material_cold->currentIndex()) {
        case 0:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Вода"));
            density_cold = 995.7/(0.984 + 0.483e-3 * T_medium(T1_c, T2_c));
            heat_capacity_cold = 4194.0 - 1.15 * T_medium(T1_c, T2_c) + 1.5e-2 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c);
            thermal_conductivity_cold = 0.553 * (1 + 0.003 * T_medium(T1_c, T2_c));
            kinem_coef_cold = (1.780e-6) / (1 + 33.7e-3*(T_medium(T1_c, T2_c)) + 221e-6 * T_medium(T1_c, T2_c)*T_medium(T1_c, T2_c));
            dinamic_coef_cold = kinem_coef_cold * density_cold;
            thermal_coef_cold = 0.132e-6 * (1 + 0.003 * T_medium(T1_c, T2_c));
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 1:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Воздух"));
            density_cold = P_c * 1000/(287.4 * (T_medium(T1_c, T2_c) + 273.15));
            heat_capacity_cold = (1.0005 + 1.1904e-4 * (T_medium(T1_c, T2_c)))*1000;
            thermal_conductivity_cold = 2.44e-2 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.82);
            dinamic_coef_cold = 1.717e-5 * qPow(((T_medium(T1_c, T2_c) + 273.15)/273.15), 0.683);
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 2:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Азот"));
            density_cold = 4.364e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 3.398e-3 * T_medium(T1_c, T2_c) + 1.219;
            heat_capacity_cold = 3.814e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 0.021e-3 * T_medium(T1_c, T2_c) + 1041;
            thermal_conductivity_cold = -3.77e-8 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 7.5e-5 * T_medium(T1_c, T2_c) + 0.024;
            dinamic_coef_cold =  -2.29e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.56e-8 * T_medium(T1_c, T2_c) + 1.66e-5;
            kinem_coef_cold = 8.223e-11 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 9.09e-8 * T_medium(T1_c, T2_c) + 1.336e-5;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            //ui->textEdit->setText(QString::number(Prantdl_cold));
            break;
        case 3:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Диоксид углерода"));
            density_cold = 8.969e-6 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) - 5.837e-3 * T_medium(T1_c, T2_c) + 1.922;
            heat_capacity_cold = -7.685e-4 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 1.04e-3 * T_medium(T1_c, T2_c) + 823.4;
            thermal_conductivity_cold = (2.733e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.072 * T_medium(T1_c, T2_c) + 14.681)*10e-4;
            dinamic_coef_cold = 1.98e-12 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 4.067e-8 * T_medium(T1_c, T2_c) + 1.376e-5;
            kinem_coef_cold = (7.904e-5 * T_medium(T1_c, T2_c) * T_medium(T1_c, T2_c) + 0.047 * T_medium(T1_c, T2_c) + 7.054)*10e-7;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 4:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 10%"));
            density_cold = 1016;
            heat_capacity_cold = 2002;
            thermal_conductivity_cold = 0.586;
            dinamic_coef_cold = 0.826e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 5:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 20%"));
            density_cold = 1040;
            heat_capacity_cold = 1915;
            thermal_conductivity_cold = 0.540;
            dinamic_coef_cold = 1.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 6:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 30%"));
            density_cold = 1073;
            heat_capacity_cold = 1830;
            thermal_conductivity_cold = 0.502;
            dinamic_coef_cold = 1.46e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 7:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 40%"));
            density_cold = 1089;
            heat_capacity_cold = 1774;
            thermal_conductivity_cold = 0.460;
            dinamic_coef_cold = 2.07e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 8:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 50%"));
            density_cold = 1115;
            heat_capacity_cold = 1659;
            thermal_conductivity_cold = 0.423;
            dinamic_coef_cold = 3.1e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 9:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 60%"));
            density_cold = 1142;
            heat_capacity_cold = 1573;
            thermal_conductivity_cold = 0.385;
            dinamic_coef_cold = 5.08e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        case 10:
            ui->TableProperties->setItem(8, 0, new QTableWidgetItem("Раствор глицерина 70%"));
            density_cold = 1169;
            heat_capacity_cold = 1487;
            thermal_conductivity_cold = 0.356;
            dinamic_coef_cold = 9.4e-3;
            kinem_coef_cold = dinamic_coef_cold / density_cold;
            thermal_coef_cold = thermal_conductivity_cold / (heat_capacity_cold * density_cold);
            Prantdl_cold = kinem_coef_cold / thermal_coef_cold;
            break;
        }

        //Вывод теплофизических параметров охлаждающего контура в консоль
        {
            double Data[7];
            QString dimension[7] = {"кг/м3", "Дж/(кг К)", "Вт/(м К)", "Па с", "м2/с", "м2/с", ""};
            QString parameter[7] = {"Плотность", "Теплоемкость", "Теплопроводность", "Динамическая вязкость", "Кинематическая вязкость", "Температуропроводность", "Число Прандтля"};
            Data[0] = density_cold;
            Data[1] = heat_capacity_cold;
            Data[2] = thermal_conductivity_cold;
            Data[3] = dinamic_coef_cold;
            Data[4] = kinem_coef_cold;
            Data[5] = thermal_coef_cold;
            Data[6] = Prantdl_cold;
            ui->TableProperties->setSpan(8,0,1,3);
            for(int row = 9; row < 16; row++) //String
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString(QString::number(Data[row-9], 'f', 8)).arg(row).arg(1));
                ui->TableProperties->setItem(row, 1, item);
                ui->TableProperties->setItem(row, 2, new QTableWidgetItem(dimension[row-9]));
                ui->TableProperties->setItem(row, 0, new QTableWidgetItem(parameter[row-9]));
            }
        }

        //Выбор материала теплообменного аппарата для дальнейшего расчета
        switch (ui->cBox_material_heat_ex->currentIndex()) {
        case 0:
            ui->TableProperties->setItem(16, 0, new QTableWidgetItem("Нержавеющая сталь"));
            density_metall = 7920;
            heat_capacity_metall = 460;
            thermal_conduc_metall = 15;
            break;
        case 1:
            ui->TableProperties->setItem(16, 0, new QTableWidgetItem("Алюминий"));
            density_metall = 2770;
            heat_capacity_metall = 922;
            thermal_conduc_metall = 130;
            break;
        case 2:
            ui->TableProperties->setItem(16, 0, new QTableWidgetItem("Титан"));
            density_metall = 4500;
            heat_capacity_metall = 530;
            thermal_conduc_metall = 22;
            break;
        case 3:
            ui->TableProperties->setItem(16, 0, new QTableWidgetItem("Медь"));
            density_metall = 8930;
            heat_capacity_metall = 381;
            thermal_conduc_metall = 480;
            break;
        }
        //Вывод теплофизических параметров материала теплообменного аппарата в консоль
        {
            double Data[3];
            QString dimension[3] = {"кг/м3", "Дж/(кг К)", "Вт/(м К)"};
            QString parameter[3] = {"Плотность", "Теплоемкость", "Теплопроводность"};
                                     Data[0] = density_metall;
            Data[1] = heat_capacity_metall;
            Data[2] = thermal_conduc_metall;
            ui->TableProperties->setSpan(16,0,1,3);
            for(int row = 17; row < 20; row++) //String
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString(QString::number(Data[row-17], 'f', 8)).arg(row).arg(1));
                ui->TableProperties->setItem(row, 1, item);
                ui->TableProperties->setItem(row, 2, new QTableWidgetItem(dimension[row-17]));
                ui->TableProperties->setItem(row, 0, new QTableWidgetItem(parameter[row-17]));
            }
            ui->TableProperties->horizontalHeader()->resizeSection(0,150);
            ui->TableProperties->horizontalHeader()->resizeSection(1,80);
            ui->TableProperties->horizontalHeader()->resizeSection(2,50);
        }

        //Тепловое решение
        /*if (ui->cBox_cavity_hot->currentIndex() == 0) //Горячий контур в трубном пространстве
        {
            delt_T = Term_pressure(ui->cBox_current_type->currentIndex(), T1_h, T2_h, T1_c, T2_c);  //Температурный напор
            power = Power(T1_h, T2_h, d_mass_h, heat_capacity_hot);                                 //Мощность теплопередачи
            area_tube_d = Tubes_area_d(d);
            v_h = Flow_rate(area_tube_d, d_mass_h, density_hot);
            Reynolds_hot = Reynolds(v_h, d, kinem_coef_hot);
            Nusselt_hot = Nusselt_d(Reynolds_hot, Prantdl_hot);
            coef_heat_tr_hot = Heat_transfer_coef(Nusselt_hot, thermal_conductivity_hot, d);
            ////////////////////////////////////////////////////////////////////////////////////
            area_tube_D = Tubes_area_D(d, D, delt);
            v_c = Flow_rate(area_tube_D, d_mass_c, density_cold);
            double d_eq = D - d;
            Reynolds_cold = Reynolds(v_c, d_eq, kinem_coef_cold);
            Nusselt_cold = Nusselt_D(Reynolds_cold, Prantdl_cold, d, D);
            coef_heat_tr_cold = Heat_transfer_coef(Nusselt_cold, thermal_conductivity_cold, d_eq);
            //Рассчет коэффициента теплопередачи
            k = Heat_transfer(coef_heat_tr_hot, coef_heat_tr_cold, delt, thermal_conduc_metall);
            F = Square(power, k, delt_T);
            l = Lenght(F, 1, d);
        }
        else                                          //Холодный контур в трубном пространстве
        {
            delt_T = Term_pressure(ui->cBox_current_type->currentIndex(), T1_h, T2_h, T1_c, T2_c);  //Температурный напор
            power = Power(T1_h, T2_h, d_mass_h, heat_capacity_hot);                                 //Мощность теплопередачи
            area_tube_d = Tubes_area_d(d);
            v_c = Flow_rate(area_tube_d, d_mass_c, density_cold);
            Reynolds_cold = Reynolds(v_c, d, kinem_coef_cold);
            Nusselt_cold = Nusselt_d(Reynolds_cold, Prantdl_cold);
            coef_heat_tr_cold = Heat_transfer_coef(Nusselt_cold, thermal_conductivity_cold, d);
            ///////////////////////////////////////////////////////////////////////////////////////
            area_tube_D = Tubes_area_D(d, D, delt);
            v_h = Flow_rate(area_tube_D, d_mass_h, density_hot);
            double d_eq = D - d;
            Reynolds_hot = Reynolds(v_c, d_eq, kinem_coef_hot);
            Nusselt_hot = Nusselt_D(Reynolds_hot, Prantdl_hot, d, D);
            coef_heat_tr_hot = Heat_transfer_coef(Nusselt_hot, thermal_conductivity_hot, d_eq);
            //Рассчет коэффициента теплопередачи
            k = Heat_transfer(coef_heat_tr_hot, coef_heat_tr_cold, delt, thermal_conduc_metall);
            F = Square(power, k, delt_T);
            l = Lenght(F, 1, d);
        }

        if (Reynolds_hot >= 10000)
            ui->Table->setItem(4, 3, new QTableWidgetItem("- турбулентный режим течения"));
        else if (Reynolds_hot < 10000 and Reynolds_hot > 2300)
            ui->Table->setItem(4, 3, new QTableWidgetItem("- переходный режим течения"));
        else
            ui->Table->setItem(4, 3, new QTableWidgetItem("- ламинарный режим течения"));

        if (Reynolds_cold >= 10000)
            ui->Table->setItem(9, 3, new QTableWidgetItem("- турбулентный режим течения"));
        else if (Reynolds_cold < 10000 and Reynolds_cold > 2300)
            ui->Table->setItem(9, 3, new QTableWidgetItem("- переходный режим течения"));
        else
            ui->Table->setItem(9, 3, new QTableWidgetItem("- ламинарный режим течения"));
        */
        data[0] = delt_T;
        data[1] = power;
        data[2] = area_tube_d;
        data[3] = v_h;
        data[4] = Reynolds_hot;
        data[5] = Nusselt_hot;
        data[6] = coef_heat_tr_hot;
        data[7] = area_tube_D;
        data[8] = v_c;
        data[9] = Reynolds_cold;
        data[10] = Nusselt_cold;
        data[11] = coef_heat_tr_cold;
        data[12] = k;
        data[13] = F;
        data[14] = l;

        //Запись в таблицу
        ui->Table->horizontalHeader()->resizeSection(0,300);
        ui->Table->horizontalHeader()->resizeSection(1,100);
        ui->Table->horizontalHeader()->resizeSection(2,100);
        ui->Table->horizontalHeader()->resizeSection(3,200);
        for(int row = 0; row < 15; row++) //String
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(QString(QString::number(data[row], 'f', 6)).arg(row).arg(1));
            ui->Table->setItem(row, 1, item);
        }
        ui->statusbar->showMessage("Расчет завершен!");
    }
    else
        ui->statusbar->showMessage("Введите данные для выполнения расчета...");
}

