#include "mainwindow.h"
#include "ui_mainwindow.h"

// #26A0DA

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    channel = NULL;
    timer = new QTimer();
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();

    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: #212121; }");
    this->setWindowTitle("AMP v1.0a");

    QPushButton * menuBtn = new QPushButton(this);
    menuBtn->setGeometry(15, 20, 30, 30);
    menuBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    menuBtn->setText("Menu");
    menuBtn->show();

    pauseBtn = new QPushButton(this);
    pauseBtn->setGeometry(375, 285, 50, 50);
    pauseBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    pauseBtn->setText("Pause");
    pauseBtn->show();

    QPushButton * forwardBtn = new QPushButton(this);
    forwardBtn->setGeometry(440, 290, 40, 40);
    forwardBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    forwardBtn->setText("Fwd");
    forwardBtn->show();

    QPushButton * backwardBtn = new QPushButton(this);
    backwardBtn->setGeometry(320, 290, 40, 40);
    backwardBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    backwardBtn->setText("Bwd");
    backwardBtn->show();

    repeatBtn = new QPushButton(this);
    repeatBtn->setGeometry(500, 295, 30, 30);
    repeatBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    repeatBtn->setText("Rpt");
    repeatBtn->show();

    QPushButton * equoBtn = new QPushButton(this);
    equoBtn->setGeometry(230, 295, 30, 30);
    equoBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    equoBtn->setText("Equo");
    equoBtn->show();

    QPushButton * shuffleBtn = new QPushButton(this);
    shuffleBtn->setGeometry(270, 295, 30, 30);
    shuffleBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    shuffleBtn->setText("Sfl");
    shuffleBtn->show();

    QPushButton * audio3dBtn = new QPushButton(this);
    audio3dBtn->setGeometry(540, 295, 30, 30);
    audio3dBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    audio3dBtn->setText("3D");
    audio3dBtn->show();

    QPushButton * cover = new QPushButton (this);
    cover->setGeometry(325, 60, 150, 150);
    cover->setStyleSheet("font-size: 18px; border: 1px solid silver; background-color: #212121; color: silver;");
    cover->setText("Cover Image");
    cover->show();

    songTitle = new QLabel(this);
    songTitle->setText("Artist - Song Name");
    songTitle->setGeometry(200, 220, 400, 30);
    songTitle->setAlignment(Qt::AlignCenter);
    songTitle->setStyleSheet("/* border: 1px solid silver; */ font-size: 20px; background-color: #212121; color: silver;");
    songTitle->show();

    QLabel * songInfo = new QLabel(this);
    songInfo->setText("Genre, 44.1k MP3");
    songInfo->setGeometry(200, 255, 400, 16);
    songInfo->setAlignment(Qt::AlignCenter);
    songInfo->setStyleSheet("/* border: 1px solid silver; */ background-color: #212121; color: gray;");
    songInfo->show();

    QLabel * spectrum = new QLabel (this);
    spectrum->setText("Pre-rendered/Live Spectrum");
    spectrum->setGeometry(15, 350, 770, 40);
    spectrum->setAlignment(Qt::AlignCenter);
    spectrum->setStyleSheet("font-size: 20px; border: 1px solid silver; background-color: #212121; color: silver;");
    spectrum->show();

    playlistWidget = new QListWidget (this);

    playlistWidget->setGeometry(15, 400, 770, 160);
    playlistWidget->setStyleSheet("padding: 10px; font-size: 14px; border: 1px solid silver; background-color: #212121; color: silver;");
    playlistWidget->show();

    QPushButton * addSong = new QPushButton (this);
    addSong->setGeometry(15, 570, 100, 20);
    addSong->setText("Add Song");
    addSong->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
    addSong->show();

    songPosition = new QLabel(this);
    songPosition->setText("00:00");
    songPosition->setGeometry(23, 365, 200, 20);
    songPosition->setAlignment(Qt::AlignLeft);
    songPosition->setStyleSheet("/* border: 1px solid silver; background-color: #212121; */ color: gray;");
    songPosition->show();

    songDuration = new QLabel(this);
    songDuration->setText("00:00");
    songDuration->setGeometry(600, 365, 180, 20);
    songDuration->setAlignment(Qt::AlignRight);
    songDuration->setStyleSheet("/* border: 1px solid silver; background-color: #212121; */ color: gray;");
    songDuration->show();

    volumeSlider = new QSlider (Qt::Horizontal, this);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setValue(100);
    volumeSlider->setGeometry(633, 300, 150, 20);
    volumeSlider->setStyleSheet("QSlider::groove:horizontal {" \
                                    "border: 1px solid #999999; " \
                                    "height: 7px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */" \
                                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"\
                                    "margin: 2px 0;"\
                                "}" \
                               "QSlider::handle:horizontal {" \
                                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); "\
                                    "border: 1px solid #5c5c5c; "\
                                    "width: 18px; " \
                                    "margin: -2px 0;  handle is placed by default on the contents rect of the groove. Expand outside the groove */ " \
                                    "border-radius: 2px; "\
                                "}");
    volumeSlider->show();

    connect(playlistWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(setActive(QListWidgetItem *)));

    connect (menuBtn, SIGNAL(clicked()), this, SLOT(test()));
    connect (addSong, SIGNAL(clicked()), this, SLOT(openFile()));

    connect (forwardBtn, SIGNAL(clicked()), this, SLOT(forward()));
    connect (backwardBtn, SIGNAL(clicked()), this, SLOT(backward()));
    connect (pauseBtn, SIGNAL(clicked()), this, SLOT(pause()));
    connect (repeatBtn, SIGNAL(clicked()), this, SLOT(changeRepeat()));

    connect (volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    cout << "Some event test..." << endl;
}
bool MainWindow::openFile ()
{
    HWND win = NULL;
    wchar_t file[MAX_PATH] = L"";

    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = win;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = file;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    ofn.lpstrTitle = L"Select a file to play";
    ofn.lpstrFilter = L"Audio Files\0*.mo3;*.xm;*.mod;*.s3m;*.it;*.mtm;*.umx;*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif)\0All files\0*.*\0\0";

    if (!GetOpenFileName(&ofn)) return false;
    else {
        Song temp(file);
        temp.setName(file);
        temp.setNameFromPath();
        wcout << temp.path << endl;

        playlist.push_back(temp);
        cout << playlist.size() << endl;

        drawPlaylist();
    }

    return true;
}
void MainWindow::drawPlaylist() {
    playlistWidget->clear();

    for (int i = 0; i < playlist.size(); i++)
    {
        QListWidgetItem *  songItem = new QListWidgetItem(playlistWidget);
        QString path = QString::fromStdWString(wstring(playlist[i].path));
        QString name = QString::fromStdWString(to_wstring(i + 1) + L". " + playlist[i].getName());

        //if (current == playlist.begin() + i)
        //    songItem->setBackgroundColor(QColor(38, 160, 218));

        songItem->setData(Qt::UserRole, i);
        songItem->setData(1, path);
        songItem->setText(name);

        playlistWidget->addItem(songItem);
   }
}
void MainWindow::setTitle () {
    wstring name = current->getName();
    if (name.length() > 32)
        name = name.substr(0, 32) + L"...";

    songTitle->setText(QString::fromStdWString(name));
}
void MainWindow::setActive(QListWidgetItem * item) {
    current = playlist.begin() + item->data(Qt::UserRole).toInt();

    if (channel != NULL)
        BASS_ChannelStop(channel);

    channel = BASS_StreamCreateFile(FALSE, current->path, 0, 0, 0);
    BASS_ChannelPlay(channel, true);
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);

    QString pos = QString::fromStdString(seconds2string(getPosition()));
    songPosition->setText(pos);
    QString len = QString::fromStdString(seconds2string(getDuration()));
    songDuration->setText(len);

    setTitle();
}
void MainWindow::forward () {
    if (channel == NULL || playlist.size() == 1)
        return;

    current++;
    cout << "Distance - " << distance (playlist.end(), current) << endl;
    if (distance (playlist.end(), current) >= 0) current = playlist.begin();

    BASS_ChannelStop(channel);
    channel = BASS_StreamCreateFile(FALSE, current->path, 0, 0, 0);
    BASS_ChannelPlay(channel, true);
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);

    QString pos = QString::fromStdString(seconds2string(getPosition()));
    songPosition->setText(pos);
    QString len = QString::fromStdString(seconds2string(getDuration()));
    songDuration->setText(len);

    setTitle();
}
void MainWindow::backward () {
    if (channel == NULL || playlist.size() == 1)
        return;

    current--;
    cout << "Distance - " << distance (playlist.begin(), current) << endl;
    if (distance (playlist.begin(), current) < 0) current = playlist.end() - 1;

    BASS_ChannelStop(channel);
    channel = BASS_StreamCreateFile(FALSE, current->path, 0, 0, 0);
    BASS_ChannelPlay(channel, true);
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);

    QString pos = QString::fromStdString(seconds2string(getPosition()));
    songPosition->setText(pos);
    QString len = QString::fromStdString(seconds2string(getDuration()));
    songDuration->setText(len);

    setTitle();
}
void MainWindow::pause ()
{
    if (channel == NULL) return;

    paused = !paused;

    if (paused) {
        pauseBtn->setStyleSheet("border: 1px solid silver; background-color: #212121; color: silver;");
        BASS_ChannelPlay(channel, false);
    }
    else {
        pauseBtn->setStyleSheet("border: 1px solid #26A0DA; background-color: #212121; color: silver;");
        BASS_ChannelPause(channel);
    }
}
void MainWindow::changeVolume (int vol)
{
    cout << vol << endl;
    volume = vol / 100.0f;
    BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);
}

string MainWindow::seconds2string (float seconds) {
    int hours = (seconds > 3600) ? (int)seconds / 3600 : 0;
    int minutes = (seconds > 60) ? ((int)seconds - hours * 3600) / 60 : 0;
    int secs = (int)seconds % 60;

    string result = "";
    if (hours != 0)
    {
        if (hours < 10) result += "0";
        result += to_string (hours);
        result += ":";
    }

    if (minutes < 10) result += "0";
    result += to_string (minutes);
    result += ":";

    if (secs < 10) result += "0";
    result += to_string (secs);

    return result;
}

void MainWindow::updateTime() {
    if (channel != NULL) {
        QString pos = QString::fromStdString(seconds2string(getPosition()));
        songPosition->setText(pos);

        if (getPosition() >= getDuration())
        {
            if (repeat) {
                BASS_ChannelStop(channel);
                channel = BASS_StreamCreateFile(FALSE, current->path, 0, 0, 0);
                BASS_ChannelPlay(channel, true);
                BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);
            }
            else if (shuffle) {
                // Stuff...
            } else {
                forward();
            }
        }
    }
}