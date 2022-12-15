# DS18B20-ZigBee-Network-Project
Project for Wireless Sensor Network (WSN)
# MÔ TẢ DỰ ÁN
Mạng hình sao cảm biến nhiệt độ DS18B20 -  Vi xử lý STM32F103C8T6 (Blue Pill) truyền thông qua Gateway xây dựng dựa trên ZigBee CC2530 + ESP32
# Mạch cảm biến - Vi xử lý
![plot]([(https://raw.githubusercontent.com/PhamVietThinh2803/DS18B20-ZigBee-Network-Project/main/Schematic/STM32-DS18B20.BMP)])
Mạch cảm biến - Vi xử lý có các chức năng cơ bản sau:
+ Dải đo nhiệt độ từ 25oC - 125oC với độ phân giải đo là 0.1oC, độ chính xác +- 1oC.
+ STM32F103C8T6 giao tiếp với DS18B20 chuẩn 1-Wire.
+ STM32F103C8T6 giao tiếp với LCD chuẩn I2C.
+ Mạch cảnh báo bằng đen LED theo 3 mức (Cao - Đỏ, Bình thường - Xanh dương, Thấp - Xanh Lá)
+ Khi nhiệt độ vượt ngưỡng, đèn cảnh báo tương ứng sẽ được bật. Khi nhiệt độ đã dưới ngưỡng vẫn cần chờ nhấn nút để thoát cảnh báo.
+ Cập nhật nhiệt độ 5 giây 1 lần. Trong thời gian chờ có thể vào trạng thái ngủ (SLEEP MODE) và thức dậy sử dụng hẹn giờ thông qua module RTC có sẵn trong vi xử lý
