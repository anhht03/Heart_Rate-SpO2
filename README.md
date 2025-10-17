# Heart_Rate-SpO2
##📘 Giới thiệu
-Dự án giúp theo dõi nhịp tim (BPM) và nồng độ oxy trong máu (SpO₂) theo thời gian thực.
-Hệ thống sử dụng:
Cảm biến MAX30102 để đo nhịp tim và SpO₂
Màn hình OLED SSD1306 để hiển thị thông số
Kết nối Blynk IoT để giám sát dữ liệu qua điện thoại
Có LED và buzzer cảnh báo khi nhịp tim vượt ngưỡng

##⚙️ Phần cứng sử dụng
-Tên linh kiện	Mô tả / Công dụng
-ESP32S	Vi điều khiển chính, kết nối WiFi
-MAX30102	Cảm biến đo nhịp tim và SpO₂
-OLED SSD1306 0.96”	Hiển thị BPM & SpO₂
-LM2596	Mạch nguồn hạ áp 5V → 3.3V
-LED + R220Ω	Báo hiệu cảnh báo
-Loa (buzzer)	Phát âm thanh cảnh báo
-Nút nhấn (SW1)	Tắt hoặc reset cảnh báo

##🧠 Chức năng chính
-Đọc nhịp tim (BPM) và SpO₂ từ cảm biến MAX30102
-Hiển thị thông số lên màn hình OLED
-Gửi dữ liệu thời gian thực lên Blynk Cloud
- cảnh báo LED + âm thanh khi BPM vượt ngưỡng
-Tắt cảnh báo bằng nút nhấn SW1

##💻 Cấu trúc thư mục dự án
-ESP32_Health_Monitor/
-├── Ysinh.ino           // Code chính ESP32
-├── README.md           // Mô tả dự án (file này)
-├── sch.jfif            // Sơ đồ nguyên lý
-└── libraries/          // Thư viện cần thiết

##📦 Thư viện cần cài đặt
-Cài trong Arduino IDE qua:
-Sketch → Include Library → Manage Libraries

##📶 Cấu hình WiFi & Blynk
-Trong code (Ysinh.ino), chỉnh lại các dòng sau:
-#define BLYNK_TEMPLATE_ID "Your_Template_ID"
-#define BLYNK_TEMPLATE_NAME "Health Monitor"
-#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

-char ssid[] = "Your_WiFi_Name";
-char pass[] = "Your_WiFi_Password";

-Trên ứng dụng Blynk:
-Tạo Template mới → đặt tên “Health Monitor”
-Thêm 2 Gauge Widgets:
-V0: Hiển thị nhịp tim (BPM)
-V1: Hiển thị SpO₂ (%)
-Copy Auth Token dán vào code

##▶️ Cách chạy
-Kết nối mạch ESP32 và cảm biến như sơ đồ
-Mở file .ino trên Arduino IDE
-Chọn board ESP32 Dev Module
-Cắm cáp USB, chọn đúng cổng COM
-Nhấn Upload để nạp code
-Mở Serial Monitor (115200 baud) để xem kết quả
-Quan sát dữ liệu hiển thị trên:
-Màn hình OLED
-Ứng dụng Blynk

##🚨 Cảnh báo hệ thống
-Điều kiện	Hành động
-BPM > 120 hoặc BPM < 50	Bật LED + Buzzer
-Nhấn nút SW1	Tắt cảnh báo
-Không phát hiện tay	Hiển thị “No finger detected”

##📱 Giao diện Blynk
-Gauge 1 (V0): Hiển thị nhịp tim (BPM)
-Gauge 2 (V1): Hiển thị SpO₂ (%)
-Có thể thêm Chart widget để hiển thị dữ liệu thời gian thực


