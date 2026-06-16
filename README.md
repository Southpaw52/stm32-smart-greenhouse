# STM32F407VG Tabanlı Akıllı Sera Otomasyon Sistemi

Bu proje, farklı bitki türlerinin değişen iklim ve ışık gereksinimlerini tek bir platformda otonom biçimde yönetebilen, modüler bir akıllı sera prototipidir. Geleneksel 8-bit ve delay() (bloklayıcı) tabanlı hobi projelerinin aksine; sistem kararlılığını artırmak için 32-bit ARM Cortex-M4 mimarisi ve Zaman Tetiklemeli Durum Makinesi (Finite State Machine - FSM) kullanılarak tasarlanmıştır.

## 🌟 Temel Özellikler
* **Otonom İklimlendirme:** BME280 sensörü ile hava sıcaklığı ve neminin, kapasitif sensör ile toprak neminin gerçek zamanlı izlenmesi ve eşik değerlere göre kontrolü.
* **Termal Yönetim ve Aydınlatma:** Harici bir ısıtıcı kullanmak yerine, yüksek güçlü bitki (Grow) LED'lerinin ürettiği atık ısı geri kazanılarak seranın pasif olarak ısıtılması.
* **Pasif Soğutma:** Ortam sıcaklığı üst sınırı aştığında PWM sinyali ile kontrol edilen servo motorlu havalandırma penceresinin otonom yönetimi.
* **Modüler Kullanıcı Arayüzü:** I2C tabanlı 16x2 LCD ekran ve menü sistemi üzerinden bitki profillerinin seçilebilmesi ve fotoperiyot/iklim eşiklerinin otomatik ayarlanması.
* **Bloklamayan (Non-Blocking) Yazılım:** `HAL_GetTick()` referans alınarak oluşturulan görev zamanlayıcısı ile mikrodenetleyicinin sensör okuma ve aktüatör kontrolü sırasında kilitlenmesinin önüne geçilmesi.

## 🛠 Donanım ve Malzeme Listesi
* **Mikrodenetleyici:** STM32F407VG (168 MHz, Donanımsal FPU, Harvard Mimarisi)
* **Sensörler:** 
  * Bosch BME280 (Sıcaklık, Nem ve Basınç - I2C ile iletişim)
  * Kapasitif Toprak Nem Sensörü (Korozyon dirençli - ADC ile iletişim)
* **Aktüatörler ve Yükler:** 
  * 12V DC Su Pompası (Röle kontrollü)
  * 12V Full Spectrum Grow LED (Röle kontrollü)
  * Servo Motor (Havalandırma penceresi için - PWM kontrollü)
* **Güç Yönetimi:** Isınma sorunlarını ve enerji kaybını önlemek amacıyla LM2596 Buck Converter ile yapılandırılmış 12V / 5V izole güç dağıtım mimarisi.
* **Arayüz:** 16x2 Karakter LCD Ekran (PCF8574 I2C modülü ile) ve menü butonları.

## 💻 Yazılım Mimarisi (Driver Katmanı)
Yazılım, kolay ölçeklenebilirlik için modüler bir yapıda C dili ile yazılmıştır:
* `bme280.c / .h`: Çevresel sensör okuma sürücüleri.
* `soil_moisture.c / .h`: ADC üzerinden analog nem verisi dönüştürme.
* `actuator.c / .h`: Röle ve PWM tabanlı servo motor kontrol katmanı.
* `lcd_display_2x16_i2c_driver.c / .h` & `menu.c / .h`: I2C haberleşmeli ekran ve menü durumu yönetimi.
* `plant_profile.c / .h`: Bitki türlerine göre optimize edilmiş eşik değeri veri yapıları.

## 🚀 Değerlendirme ve Gelecek Çalışmalar
Bu sistemin ilerleyen versiyonlarında sisteme entegre edilmesi planlanan özellikler:
* Sisteme bir Wi-Fi modülü dahil edilerek sensör verilerinin bulut ortamına (cloud logging) aktarılması ve uzaktan IoT tabanlı kontrol sağlanması.
* Kapalı sera içi gaz dengesinin takibi ve bitki veriminin maksimize edilmesi amacıyla sisteme CO2 (Karbondioksit) sensörü entegrasyonunun yapılması.
* Yaz aylarındaki aşırı sıcaklara karşı koyabilmek için fan destekli aktif soğutma ünitelerinin eklenmesi.
* Toplanan verilerin yapay zeka algoritmalarıyla işlenerek dinamik sulama optimizasyonlarının gerçekleştirilmesi.
