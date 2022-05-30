#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <QMainWindow>


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
    void on_Load_clicked();
    void updatechanges();
    void on_Filter_clicked();
    void merge_photo();
    void shuffle_photo(std::string);                 // Main Filter function..
    void on_Filter_2_clicked();
    void on_Clear_clicked();
    void on_Filter_3_clicked();
    void on_Filter_4_clicked();
    void on_Apply_clicked();
    void on_Filter_5_clicked();
    void on_Apply2_clicked();
    void on_Apply3_clicked();
    void on_Filter_6_clicked();
    void on_Apply4_clicked();
    void on_Filter_7_clicked();
    void on_Filter_8_clicked();
    void on_Apply5_clicked();
    void on_Filter_11_clicked();
    void on_Filter_12_clicked();
    void on_Apply6_clicked();
    void on_Filter_10_clicked();
    void on_Filter_9_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // PHOTOSHOP_H
