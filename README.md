# Heart_Rate-SpO2
## 📘 Giới thiệu
 Dự án nhằm xây dựng một thiết bị đo nhịp tim (Heart Rate) và nồng độ oxy trong máu (SpO₂) theo thời gian thực, sử dụng vi điều khiển ESP32S kết hợp với cảm biến MAX30102. Hệ thống hiển thị dữ liệu lên màn hình OLED, đồng thời có khả năng cảnh báo bằng đèn LED và còi buzzer khi các thông số vượt ngưỡng nguy hiểm. Ngoài ra, dữ liệu được đồng bộ lên ứng dụng Blynk để theo dõi từ xa qua Internet.
  
## ⚙️ Phần cứng sử dụng
| Thiết bị | Chức năng |
|-----------|------------------|
| **ESP32S** | Vi điều khiển chính, kết nối Wi-Fi |
| **MAX30102** | Cảm biến đo nhịp tim và SpO₂ |
| **OLED** | Hiển thị BPM và SpO₂ |
| **LM2596** | Mạch nguồn hạ áp 5V → 3.3V |
| **LED + R220Ω** | Báo hiệu cảnh báo |
| **Loa (buzzer)** | Phát âm thanh cảnh báo |
| **Nút nhấn** | Tắt hoặc reset cảnh báo |

## 🧠 Chức năng chính
- Đọc nhịp tim (BPM) và SpO₂ từ cảm biến MAX30102
- Hiển thị thông số lên màn hình OLED
- Gửi dữ liệu thời gian thực lên Blynk Cloud
- Cảnh báo LED + âm thanh khi BPM vượt ngưỡng
- Tắt cảnh báo bằng nút nhấn SW1

## ▶️ Cách chạy
- Kết nối mạch ESP32 và cảm biến như sơ đồ
- Mở file .ino trên Arduino IDE
- Chọn board ESP32 Dev Module
- Cắm cáp USB, chọn đúng cổng COM
- Nhấn Upload để nạp code
- Mở Serial Monitor để xem kết quả
- Quan sát dữ liệu hiển thị trên: Màn hình OLED và Ứng dụng Blynk

## 🚨 Cảnh báo hệ thống
- BPM > 120 hoặc BPM < 50	Bật LED + Buzzer
- Nhấn nút SW1	Tắt cảnh báo
- Không phát hiện tay	Hiển thị “No finger detected”

## 📱 Giao diện Blynk
- Gauge 1 (V0): Hiển thị nhịp tim (BPM)
- Gauge 2 (V1): Hiển thị SpO₂ (%)
- Có thể thêm Chart widget để hiển thị dữ liệu thời gian thực


