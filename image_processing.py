import cv2
import serial
import time

cam = cv2.VideoCapture(0)

# ret, flame = cam.read()


def UART_read(ser):
    line = ser.read()
    print(line)


def UART_send(ser):
    ser.write(str.encode(input()))


def UART_read_write():
    ser = serial.Serial("COM3", timeout=None)
    while True:
        # UART_send(ser)
        time.sleep(0.5)
        UART_read(ser)
    

def cam_read(from_):
    try:
        while True:
            ret, flame = from_.read()
            cv2.imshow("capture", flame)
            cam_capture_or_ret(flame)
    except KeyboardInterrupt:
        print("key interrupt detected")
        cv2.destroyAllWindows()


def cam_capture(from_):
    ret, flame = from_.read()
    cv2.imwrite("data/get_capture.png", flame)
    return 0


def cam_capture_or_ret(flame):
    key = cv2.waitKey(10)
    if key == 13:
        cv2.imwrite("data/get_capture.png", flame)
    elif key == 27:
        cv2.destroyAllWindows()


def check_ID():
    import serial.tools.list_ports

    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        print(p)
        print(p.device)
        print(p.name)
        print(p.description)
        print(p.hwid)
        print(p.vid)
        print(p.pid)
        print(p.serial_number)
        print(p.location)
        print(p.manufacturer)
        print(p.product)
        print(p.interface)


def is_need_resque(ser):
    """
    fixme: startなどの信号文字列にして、誤検知を防ぐ
    """
    header = UART_read(ser)
    return header == "S"


def get_picture(ser):
    if is_need_resque(ser):
        cam_capture()
    return 0



# check_ID()
# UART_read_write()
# cam_read(cam)