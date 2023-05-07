#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Aides.h"
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
    void on_pushButton_pdf_clicked();
    void on_pushButton_ajout_image_clicked();
    void on_pushButton_notification_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_statistique_clicked();



    void on_pushButton_ajouter_clicked();
    void on_pushButton_annuler_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_afficher_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    // dans votre classe MainWindow
    void showStockExpiredNotification();



private:
    Ui::MainWindow *ui;
    Aides a;
};
#endif // MAINWINDOW_H
