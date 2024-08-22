/*
 * Copyright 2024 AliTech Works
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool frameClicked = false;
    bool labelInputEnabled = false;
    QFrame *clickedFrame = nullptr;

    QList<QString> gameGeneratedFrames;
    QList<QString> errorFrames;
    QList<int> findPossibleSolutions();
    void checkSolution();
    void checkFrames();

public slots:
    void startNewGame(int brojOtkrivenihPolja);

private:
    Ui::MainWindow *ui;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_findPossibleSolutions_pushButton_clicked();
    void on_startNewGame_pushButton_clicked();
};

#endif // MAINWINDOW_H
