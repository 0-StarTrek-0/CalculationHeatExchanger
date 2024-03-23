#ifndef CASING_H
#define CASING_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QRegularExpressionValidator>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

#include "Solution.h"

static QString NameFile2 = "";

namespace Ui {
class Casing;
}

class Casing : public QMainWindow
{
    Q_OBJECT

private:
    double T1_h, T2_h, d_mass_h, P_h, v;
    double T1_c, T2_c, d_mass_c, P_c;
    double d, D, d_eq, n, m, delt, h, delt_d;

    double density_hot, density_cold;
    double heat_capacity_hot, heat_capacity_cold;
    double thermal_conductivity_hot, thermal_conductivity_cold;
    double kinem_coef_hot, kinem_coef_cold;
    double dinamic_coef_hot, dinamic_coef_cold;
    double thermal_coef_hot, thermal_coef_cold;
    double Prantdl_hot, Prantdl_cold;

    double delt_T, power;
    double area_tube, area_tubes, area_interpipe;
    double v_h, v_c;

    double Nusselt_hot, Nusselt_cold;
    double Reynolds_hot, Reynolds_cold;
    double heat_transfer_hot, heat_transfer_cold;
    double coef_heat_tr_hot, coef_heat_tr_cold;
    double k, l, F;

    double density_metall;
    double heat_capacity_metall;
    double thermal_conduc_metall;

    double data[18];
    double A, a, b;

public:
    explicit Casing(QWidget *parent = nullptr);
    ~Casing();

private slots:
    void on_Exit_menu_triggered();

    void on_Create_menu_triggered();

    void on_Open_menu_triggered();

    void on_Save_as_menu_triggered();

    void on_Save_menu_triggered();

    void on_Clean_menu_triggered();

    void on_Check_menu_triggered();

    void on_T_ex_cold_menu_triggered();

    void on_T_ex_hot_menu_triggered();

    void on_Button_save_exel_clicked();

    void on_Button_clear_table_clicked();

    void on_Button_Exit_clicked();

    void on_Button_Start_clicked();

    void on_Start_menu_triggered();

private:
    Ui::Casing *ui;
};

#endif // CASING_H
