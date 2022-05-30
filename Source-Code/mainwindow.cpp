#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bmplib.cpp"
#include "QFileDialog"
#include <QMessageBox>
#include <QDebug>
#include <QRadioButton>
#include <QInputDialog>
#include <QIcon>

unsigned char image[SIZE][SIZE][RGB];
unsigned char saveimage[SIZE][SIZE][RGB];
unsigned char mergeimage[SIZE][SIZE][RGB];


QImage simage;
QImage mergeimage2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("CLOWNS PHOTOSHOP");

    QPixmap pix("C:/Icons/logo.jpg");
    ui->Before->setStyleSheet("border: 1px solid black;");
    ui->After->setStyleSheet("border: 1px solid black;");
    setWindowIcon(QIcon("C:/Icons/iconlogo.png"));


    ui->Logo->setPixmap(pix);
    ui->FlipOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->groupBox->setVisible(false);


}


MainWindow::~MainWindow()
{
    delete ui;
}

void blackandwhite()
{
    float avg=0;
      for (int i = 0; i < SIZE; i++)
      {
        for (int j = 0; j< SIZE; j++)
        {
            avg = (image[i][j][0] + image[i][j][1]+ image[i][j][2]) /3; // TAKE THE AVERAGE OF EACH PIXEL
            if (avg < 127) // CHECK IF AVERAGE LESS THAN 127
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[i][j][r] = 0;
                }

            }
            else
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[i][j][r] = 255;
                }

            }
        }
      }
}

void MainWindow::merge_photo() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files(*.bmp)"));
    mergeimage2.load(filename);
    readRGBBMP(filename.toStdString().c_str(),mergeimage);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                saveimage[i][j][r] = ((image[i][j][r])+(mergeimage[i][j][r]))/2;
            }
        }
    }
}

void invert_photo() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                saveimage[i][j][r] = 255-(image[i][j][r]);
            }
        }
    }
}

void flip_photo(bool choose)
{
    int z = 0 ;
    if (choose){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[z][j][r] = (image[i][j][r]);
                }
            }
            z++;
        }
    }
    else if (!choose)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256,y = 0; j >= 0 ;j-- , y++)
            {
                for (int r =0 ; r<RGB ;r++)
                {
                    saveimage[i][y][r] = (image[i][j][r]);
                }
            }
        }
    }
}

void rotate_photo(int choose) {
    int z = 0 ;
    if (choose == 1){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                saveimage[z][j][r] = (image[i][256-j][r]);
                }
            }
            z++;
        }
    }
    else if (choose == 2){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256, y = 0 ; j >= 0 ; j-- , y++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                    saveimage[i][y][r] = (image[j][i][r]);
                }
            }
        }
    }
    else if (choose == 3){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                for (int r =0 ; r<RGB;r++)
                {
                saveimage[i][j][r] = (image[j][256-i][r]);
                }
            }
        }
    }
}
void do_dark(int want)
{
    if(want == 1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[i][j][x] * 0.25;
                }
            }
        }
    }
    else if(want == 2)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[i][j][x]+ ((255 - image[i][j][x]) * 0.75);
                }
            }
        }
    }
}

void do_shrink(int want)
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                saveimage[i][j][x] = 255;
            }
        }
    }
    if(want == 1)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 2; i++)
        {
            for(int j = 0; j < SIZE / 2; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 2;
                if(v > 255)
                {
                    v = 0; c += 2;
                }
            }
        }
    }
    else if(want == 2)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 3; i++)
        {
            for(int j = 0; j < SIZE / 3; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 3;
                if(v > 252)
                {
                    v = 0; c += 3;
                }
            }
        }
    }
    else if(want == 3)
    {
        int c = 0, v = 0;
        for(int i = 0; i < SIZE / 4; i++)
        {
            for(int j = 0; j < SIZE / 4; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[c][v][x];
                }
                v += 4;
                if(v > 252)
                {
                    v = 0; c += 4;
                }
            }
        }
    }

}

void enlarge_photo(int choose) {
    if (choose == 1)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                    saveimage[y][k][r] = image[i][j][r];
                    saveimage[y][k+1][r] = image[i][j][r];
                    saveimage[y+1][k][r] = image[i][j][r];
                    saveimage[y+1][k+1][r] = image[i][j][r];

                }

            }
        }
    }
    else if (choose == 2)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }
            }
        }
    }
    else if (choose == 3)
    {
        for (int i = 128, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }
            }
        }
    }
    else if (choose == 4)
    {
        for (int i = 127, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                saveimage[y][k][r] = image[i][j][r];
                saveimage[y][k+1][r] = image[i][j][r];
                saveimage[y+1][k][r] = image[i][j][r];
                saveimage[y+1][k+1][r] = image[i][j][r];
                }

            }
        }
    }
}
void dark() // Darken The Image
{
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int x = 0; x < RGB; x++)
                {
                    saveimage[i][j][x] = image[i][j][x] * 0.22999;

                }
            }
        }

}

void do_detect()
{
    dark();
    int ix[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}}; // To detect the Horizontal Edges
    int iy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}}; // To detect the Vertical Edges
    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                float sumx = 0, sumy = 0;
                for(int f = i, c = 0; f < i+3 && c < 3; f++, c++)
                {
                    for(int y = j, v = 0; y < j+3 && v < 3; y++, v++)
                    {
                        sumx += (saveimage[f][y][x] * ix[c][v]);
                        sumy += (saveimage[f][y][x] * iy[c][v]);
                    }
                }
                saveimage[i][j][x] = sqrt(sumx * sumx + sumy * sumy);// Taking the Average of the horizontal and the vertical edges
            }
        }
    }
    for(int i = 1; i < 255; i++)
    {
        for(int j = 1 ; j < 255; j++)
        {
            for(int r = 0; r < RGB; r++)
            {
                saveimage[i][j][r] = 255 - saveimage[i][j][r];
            }

        }
    }

}
void do_blur()
{
    int sum = 0;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                saveimage[i][j][x] = image[i][j][x];
            }
        }
    }
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int x = 0; x < RGB; x++)
            {
                sum = 0;
                for(int c = i - 5; c < i + 6; c++)
                {
                    for(int v = j - 5; v < j + 6; v++)
                    {
                        if(c >= 0 && v >= 0 && c < 256 && v < 256)
                            sum += image[c][v][x];
                    }
                }
                saveimage[i][j][x] = sum / 121;
            }
        }
    }

}
void mirror_image(std::string choose){
    if (choose == "Right")
    {
        for (int i=0; i<SIZE; i++)
        {
          for (int j=0; j<SIZE; j++)
          {
              for (int r =0 ; r<RGB ; r++)
              {
                    saveimage[i][j][r] = image[i][256-j][r];
              }
          }
        }
    }
    else if (choose == "Lower")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0; j<SIZE; j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                    saveimage[i][j][r] = image[256-i][j][r];
                }
            }
        }
    }
    else if (choose == "Left")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0 ,y=0; j<SIZE; j++,y++)
            {
               for (int r =0 ; r<RGB ; r++)
               {
                   if (j < 128)
                    {
                        saveimage[i][y][r] = image[i][j][r];
                    }
                    else
                    {
                        saveimage[i][y][r] = image[i][256-j][r];
                    }
               }
            }
        }
    }
    else if (choose == "Upper")
    {
        for (int i=0,y=0; i<SIZE; i++,y++)
        {
            for (int j=0 ; j<SIZE; j++)
            {
                for (int r =0 ; r<RGB ; r++)
                {
                   if (i < 128)
                    {
                        saveimage[y][j][r] = image[i][j][r];
                    }
                    else
                    {
                        saveimage[y][j][r] = image[256-i][j][r];
                    }
                }
            }
        }
    }

}
void first_quarter(int quarter) // first quarter function..
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        for (int j = 0 ; j < 128 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 0)
                {
                    saveimage[i][j][r] = image[i][j][r];// add first quarter into quarter 1
                }
                else if (quarter == 1)
                {
                    saveimage[i][x][r] = image[i][j][r];// add first quarter into quarter 2
                }
                else if (quarter == 2)
                {
                    saveimage[y][j][r] = image[i][j][r];// add first quarter into quarter 3
                }
                else if (quarter == 3)
                {
                    saveimage[y][x][r] = image[i][j][r];// add first quarter into quarter 4

                }
            }
            x++;
        }
    y++;
    }
}
void second_quarter(int quarter) // Second quarter function..
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        //int x = 128;
        int l = 0;
        for (int j = 128 ; j <= 256 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 1)
                {
                    saveimage[i][j][r] = image[i][j][r]; // add Second quarter into quarter 2
                }
                else if (quarter == 0)
                {
                    saveimage[i][l][r] = image[i][j][r]; // add Second quarter into quarter 1
                }
                else if (quarter == 3)
                {
                    saveimage[y][j][r] = image[i][j][r]; // add Second quarter into quarter 4
                }
                else if (quarter == 2)
                {
                    saveimage[y][l][r] = image[i][j][r]; // add Second quarter into quarter 3

                }
            }
            l++;
        }
    y++;
    }
}
void third_quarter(int quarter) // Third quarter function..
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 128;
        int l = 0;
        for (int j = 0 ; j < 128 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 2)
                {
                    saveimage[i][j][r] = image[i][j][r]; // add Third quarter into quarter 3
                }
                else if (quarter == 3)
                {
                    saveimage[i][x][r] = image[i][j][r]; // add Third quarter into quarter 4
                }
                else if (quarter == 0)
                {
                    saveimage[y][l][r] = image[i][j][r]; // add Third quarter into quarter 1

                }
                else if (quarter == 1)
                {
                    saveimage[y][x][r] = image[i][j][r]; // add Third quarter into quarter 2

                }
            }
            x++;
            l++;
        }
    y++;
    }
}
void fourth_quarter(int quarter) // Fourth quarter function..
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 0;
        int l = 128;
        for (int j = 128 ; j <= 256 ;j++)
        {
            for (int r =0 ; r<RGB ;r++)
            {
                if (quarter == 3)
                {
                    saveimage[i][j][r] = image[i][j][r];// add Fourth quarter into quarter 4
                }
                else if (quarter == 2)
                {
                    saveimage[i][x][r] = image[i][j][r];// add Fourth quarter into quarter 3
                }
                else if (quarter == 0)
                {
                    saveimage[y][x][r] = image[i][j][r];// add Fourth quarter into quarter 1
                    x++;
                }
                else if (quarter == 1)
                {
                    saveimage[y][l][r] = image[i][j][r];// add Fourth quarter into quarter 2

                }
            }
        x++;
        l++;
        }
    y++;
    }
}
void MainWindow::shuffle_photo(std::string choose) {                      // Main Filter function..
    string arr ={'1','2','3','4'};
    int check = 0;
    //check if there's a duplication or no ...
    for (int i = 0 ; i < 4 ;i++)
        {
        for (int y = 0 ; y < 4 ; y++)
            {
                if ( choose[0] != choose[1] && choose[0] != choose[2] && choose[0] != choose[3])
                {
                    if (choose[1] != choose[2] && choose[1] != choose[3] && choose[2] != choose[3])
                    {
                        if ( choose[i] == arr[y])     // check if user add a correct numbers..
                        {
                                check += 1;
                                continue;
                        }
                    }
                }
            }
        }
    if (check == 4)
    {
        for ( int i = 0 ; i < 4 ; i++)
        {
            if (choose[i] == '1' ) // i => the place of the quarter 1
            {
                first_quarter(i);
            }
            else if (choose[i] == '2' ) // i => the place of the quarter 2
            {
                second_quarter(i);
            }
            else if (choose[i] == '3' ) // i => the place of the quarter 3
            {
                third_quarter(i);
            }
            else if (choose[i] == '4' ) // i => the place of the quarter 4
            {
                fourth_quarter(i);
            }
        }
    }else
    {
        QMessageBox::information(this,"SuffleFilter","there's a duplication in Sequnce");
    }
}
void MainWindow::updatechanges()
{
    string hahah ="temp.bmp";
    writeRGBBMP("temp.bmp", saveimage);
    QString qstr = QString::fromStdString(hahah);
    simage.load(qstr);
    ui->After->setPixmap(QPixmap::fromImage(simage));

}

void MainWindow::on_Load_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files(*.bmp)"));
  simage.load(filename);
  readRGBBMP(filename.toStdString().c_str(),image);
  ui->Before->setPixmap(QPixmap::fromImage(simage));
}


void MainWindow::on_Clear_clicked()
{
    string temp ="temp2.bmp";
    writeRGBBMP("temp.bmp", image);
    QString qstr = QString::fromStdString(temp);
    simage.load(qstr);
    ui->After->setPixmap(QPixmap::fromImage(simage));
}


void MainWindow::on_Filter_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    blackandwhite();
    updatechanges();
}


void MainWindow::on_Filter_2_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    invert_photo();
    updatechanges();
}

void MainWindow::on_Filter_3_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    merge_photo();
    updatechanges();

}


void MainWindow::on_Filter_4_clicked()
{
    ui->groupBox->setVisible(false);
   ui->MirrorOptions->setVisible(false);
   ui->EnlargeOptions->setVisible(false);
   ui->ShrinkOptions->setVisible(false);
   ui->DkLgOptions->setVisible(false);
   ui->RotateOptions->setVisible(false);
   ui->FlipOptions->setVisible(true);
}

void MainWindow::on_Apply_clicked()
{
    if(ui->AA->isChecked())
    {
        flip_photo(true);
        updatechanges();
        ui->FlipOptions->setVisible(false);

    }
    if(ui->VV->isChecked())
    {
        flip_photo(false);
        updatechanges();
        ui->FlipOptions->setVisible(false);

    }

}


void MainWindow::on_Filter_5_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->RotateOptions->setVisible(true);
}

void MainWindow::on_Apply2_clicked()
{
    if(ui->R90->isChecked())
    {
        rotate_photo(3);
        updatechanges();
        ui->RotateOptions->setVisible(false);

    }
    if(ui->R180->isChecked())
    {
        rotate_photo(1);
        updatechanges();
        ui->RotateOptions->setVisible(false);
    }
    if(ui->R270->isChecked())
    {
        rotate_photo(2);
        updatechanges();
        ui->RotateOptions->setVisible(false);

    }
}





void MainWindow::on_Filter_6_clicked()
{
    ui->MirrorOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->DkLgOptions->setVisible(true);

}

void MainWindow::on_Apply3_clicked()
{
    if(ui->DK->isChecked())
    {
        do_dark(1);
        updatechanges();
        ui->DkLgOptions->setVisible(false);
    }
    if(ui->LG->isChecked())
    {
        do_dark(2);
        updatechanges();
        ui->DkLgOptions->setVisible(false);

    }
}

void MainWindow::on_Filter_7_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(true);
}

void MainWindow::on_Apply4_clicked()
{
    if(ui->S12->isChecked())
    {
        do_shrink(1);
        updatechanges();
        ui->ShrinkOptions->setVisible(false);
    }
    if(ui->S13->isChecked())
    {
        do_shrink(2);
        updatechanges();
        ui->ShrinkOptions->setVisible(false);
    }
    if(ui->S14->isChecked())
    {
        do_shrink(3);
        updatechanges();
        ui->ShrinkOptions->setVisible(false);

    }
}




void MainWindow::on_Filter_8_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(true);

}


void MainWindow::on_Apply5_clicked()
{
    if(ui->A1->isChecked())
    {
        enlarge_photo(1);
        updatechanges();
        ui->EnlargeOptions->setVisible(false);
    }
    if(ui->A2->isChecked())
    {
        enlarge_photo(2);
        updatechanges();
        ui->EnlargeOptions->setVisible(false);
    }
    if(ui->A3->isChecked())
    {
        enlarge_photo(3);
        updatechanges();
        ui->EnlargeOptions->setVisible(false);

    }
    if(ui->A4->isChecked())
    {
        enlarge_photo(4);
        updatechanges();
        ui->EnlargeOptions->setVisible(false);

    }
}


void MainWindow::on_Filter_11_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    do_detect();
    updatechanges();
}

void MainWindow::on_Filter_12_clicked()
{
    ui->groupBox->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    do_blur();
    updatechanges();
}

void MainWindow::on_Filter_10_clicked()
{
    ui->groupBox->setVisible(false);
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->MirrorOptions->setVisible(true);

}
void MainWindow::on_Apply6_clicked()
{
    if(ui->M1->isChecked())
    {
        mirror_image("Left");
        updatechanges();
        ui->MirrorOptions->setVisible(false);
    }
    if(ui->M2->isChecked())
    {
        mirror_image("Right");
        updatechanges();
        ui->MirrorOptions->setVisible(false);
    }
    if(ui->M3->isChecked())
    {
        mirror_image("Upper");
        updatechanges();
        ui->MirrorOptions->setVisible(false);

    }
    if(ui->M4->isChecked())
    {
        mirror_image("Lower");
        updatechanges();
        ui->MirrorOptions->setVisible(false);
    }
}


void MainWindow::on_pushButton_clicked()
{
    int check = 0;
    ui->lineEdit->text();
    QString Input =  ui->lineEdit->text();
    string haha = Input.toStdString().c_str();
    if((haha[0] == '1' || haha [0] == '2' || haha[0] == '3' || haha[0] == '4' ) && haha.length() == 4)
    {
        if(haha[1] == '1' || haha [1] == '2' || haha[1] == '3' || haha[1] == '4')
        {
            if(haha[2] == '1' || haha [2] == '2' || haha[2] == '3' || haha[2] == '4')
            {
                if(haha[3] == '1' || haha [3] == '2' || haha[3] == '3' || haha[3] == '4')
                {
                        shuffle_photo(haha);
                        updatechanges();
                }
                else
                {
                    check += 1;
                }
            }
            else
            {
                check += 1;
            }
        }
     else {
             check += 1;
           }
    }
    else
    {
        QMessageBox::information(this,"Shuffle","Wrong !! , Only Numbers Between [1,2,3,4] and Length Should be 4");

    }
    if(check != 0 )
        QMessageBox::information(this,"Shuffle","Wrong !! , Only Numbers Between [1,2,3,4] and Length Should be 4");

    ui->lineEdit->clear();
    ui->groupBox->setVisible(false);

}


void MainWindow::on_Filter_9_clicked()
{
    ui->DkLgOptions->setVisible(false);
    ui->RotateOptions->setVisible(false);
    ui->FlipOptions->setVisible(false);
    ui->ShrinkOptions->setVisible(false);
    ui->EnlargeOptions->setVisible(false);
    ui->MirrorOptions->setVisible(false);
    ui->groupBox->setVisible(true);

}

void MainWindow::on_pushButton_2_clicked()
{
    QString saveFilePath = QFileDialog::getSaveFileName(this,tr("Save Image"),"untitled",tr("images(*.bmp)"));
    simage.save(saveFilePath);
}

