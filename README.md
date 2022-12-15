# DS18B20-ZigBee-Network-Project
Project for Wireless Sensor Network (WSN)
# MÔ TẢ DỰ ÁN
Mạng hình sao cảm biến nhiệt độ DS18B20 -  Vi xử lý STM32F103C8T6 (Blue Pill) truyền thông qua Gateway xây dựng dựa trên ZigBee CC2530 + ESP32
# Mạch cảm biến - Vi xử lý
![plot](https://github.com/PhamVietThinh2803/DS18B20-ZigBee-Network-Project/blob/main/Schematic/Schematic.png)
Mạch cảm biến - Vi xử lý có các chức năng cơ bản sau:
+ Dải đo nhiệt độ từ 25oC - 125oC với độ phân giải đo là 0.1oC, độ chính xác +- 1oC.
+ STM32F103C8T6 giao tiếp với DS18B20 chuẩn 1-Wire.
+ STM32F103C8T6 giao tiếp với LCD chuẩn I2C.
+ Mạch cảnh báo bằng đen LED theo 3 mức (Cao - Đỏ, Bình thường - Xanh dương, Thấp - Xanh Lá)
+ Khi nhiệt độ vượt ngưỡng, đèn cảnh báo tương ứng sẽ được bật. Khi nhiệt độ đã dưới ngưỡng vẫn cần chờ nhấn nút để thoát cảnh báo.
+ Cập nhật nhiệt độ 5 giây 1 lần. Trong thời gian chờ có thể vào trạng thái ngủ (SLEEP MODE) và thức dậy sử dụng hẹn giờ thông qua module RTC có sẵn trong vi xử lý
# Cấu hình chân I/O cho STM32 trong CubeMX
![plot](https://github.com/PhamVietThinh2803/DS18B20-ZigBee-Network-Project/blob/main/Code/IO.png)
Lưu ý: Ngắt ngoài kích hoạt bằng nút nhấn đặt ở chế độ xung sườn xuống, vì vậy, khi cấu hình ta chọn Pull-up chân B15 nối 1 đầu nút nhấn,
đầu còn lại nối vào trở 1K như trong Schematic
# Cấu hình Clock 
![plot](https://github.com/PhamVietThinh2803/DS18B20-ZigBee-Network-Project/blob/main/Code/Clock.png)
Chọn nguồn cấp xung Clock cho cả hệ thống là thạch anh ngoại (HSE) 
# Cấu hình Timer
Tránh sử dụng hàm HAL_Delay() do đây cũng là một hàm ngắt của hệ thống, sử dụng không đúng cách có thể gây treo hệ thống, nên ở đây ta sử dụng
Delay Timer. Timer trong STM32 được cấp bởi bộ APB2. Đặt tần số xung Clock lên tối đa là 72MHz.
Ta đặt giá trị bộ chia tần là 72 để mỗi lần đếm Timer mất 1 us (72Mhz/72 = 1Mhz --> T = 1 us)
![plot](https://github.com/PhamVietThinh2803/DS18B20-ZigBee-Network-Project/blob/main/Code/Timer.png)
