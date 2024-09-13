#pragma once

#include <memory>

#include <QFrame>
#include <QLabel>
#include <QMap>
#include <QMovie>

#include "selfdrive/ui/ui.h"

typedef QPair<QPair<QString, QString>, QColor> ItemStatus;
Q_DECLARE_METATYPE(ItemStatus);

class Sidebar : public QFrame {
  Q_OBJECT
  Q_PROPERTY(ItemStatus connectStatus MEMBER connect_status NOTIFY valueChanged);
  Q_PROPERTY(ItemStatus pandaStatus MEMBER panda_status NOTIFY valueChanged);
  Q_PROPERTY(ItemStatus tempStatus MEMBER temp_status NOTIFY valueChanged);
  Q_PROPERTY(QString netType MEMBER net_type NOTIFY valueChanged);
  Q_PROPERTY(int netStrength MEMBER net_strength NOTIFY valueChanged);

  // FrogPilot properties
  Q_PROPERTY(ItemStatus cpuStatus MEMBER cpu_status NOTIFY valueChanged)
  Q_PROPERTY(ItemStatus memoryStatus MEMBER memory_status NOTIFY valueChanged)
  Q_PROPERTY(ItemStatus storageStatus MEMBER storage_status NOTIFY valueChanged)

public:
  explicit Sidebar(QWidget* parent = 0);

signals:
  void openSettings(int index = 0, const QString &param = "");
  void valueChanged();

public slots:
  void offroadTransition(bool offroad);
  void updateState(const UIState &s);

protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void drawMetric(QPainter &p, const QPair<QString, QString> &label, QColor c, int y);

  QPixmap home_img, flag_img, settings_img;
  bool onroad, flag_pressed, settings_pressed;
  const QMap<cereal::DeviceState::NetworkType, QString> network_type = {
    {cereal::DeviceState::NetworkType::NONE, tr("--")},
    {cereal::DeviceState::NetworkType::WIFI, tr("Wi-Fi")},
    {cereal::DeviceState::NetworkType::ETHERNET, tr("ETH")},
    {cereal::DeviceState::NetworkType::CELL2_G, tr("2G")},
    {cereal::DeviceState::NetworkType::CELL3_G, tr("3G")},
    {cereal::DeviceState::NetworkType::CELL4_G, tr("LTE")},
    {cereal::DeviceState::NetworkType::CELL5_G, tr("5G")}
  };

  const QRect home_btn = QRect(60, 860, 180, 180);
  const QRect settings_btn = QRect(50, 35, 200, 117);
  const QColor good_color = QColor(255, 255, 255);
  const QColor warning_color = QColor(218, 202, 37);
  const QColor danger_color = QColor(201, 34, 49);

  ItemStatus connect_status, panda_status, temp_status;
  QString net_type;
  int net_strength = 0;

private:
  std::unique_ptr<PubMaster> pm;

  // FrogPilot widgets
  void showEvent(QShowEvent *event);
  void updateIcon(QLabel *&label, QMovie *&gif, const QString &gifPath, const QRect &btnRect, const QString &pngPath, bool &isGif);
  void updateIcons();

  // FrogPilot variables
  Params params;

  ItemStatus cpu_status, memory_status, storage_status;

  bool isCPU;
  bool isFahrenheit;
  bool isGPU;
  bool isHomeGif;
  bool isIP;
  bool isMemoryUsage;
  bool isNumericalTemp;
  bool isRandomEvents;
  bool isSettingsGif;
  bool isSidebarMetrics;
  bool isStorageLeft;
  bool isStorageUsed;

  QColor sidebar_color1;
  QColor sidebar_color2;
  QColor sidebar_color3;

  QLabel *home_label;
  QLabel *settings_label;

  QMovie *home_gif;
  QMovie *settings_gif;

  QString flagPngPath;
  QString homeGifPath;
  QString homePngPath;
  QString max_temp;
  QString randomEventGifPath;
  QString settingsGifPath;
  QString settingsPngPath;
};