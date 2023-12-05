import cv2
import serial
import time
import numpy as np
import subprocess
import socket

# ret, flame = cam.read()


def cam_init(camnum):
    """
    カメラのinit関数。
    camnum番のウェブカメのID(?)を返す。
    """
    return cv2.VideoCapture(camnum)


def UART_init(name, baud_rate, to):
    """
    シリアル通信のinit関数。
    シリアルのID(?)を返す。
    """
    return serial.Serial(name, baud_rate, timeout=to)


def Processing_init(host, port):
    socket_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_client.connect((host, port))
    return socket_client


def UART_read(ser):
    """
    serのポートから1行読み出し、その値を返す。
    """
    line = ser.readline()
    return line


def cam_capture(from_):
    """
    from_のカメラで受け取った画像を、/dataにget_capture.pngとして保存する。
    """
    ret, flame = from_.read()
    cv2.imwrite("data/get_capture.png", flame)


def check_data(data):
    return data == [84, 63, 146]


def sct_send(socket_client, n):
    socket_client.send(n.to_bytes(1, "little"))


def main():
    #processing - init
    host = "127.0.0.1"
    port = 10001

    # initialize
    ser = UART_init("COM3", 115200, 5)
    cam = cam_init(0)
    socket_client = Processing_init(host, port)
    print("start")
    try:
        while True:
            data_bytes = UART_read(ser).hex()
            data = [data_bytes[i:i+2] for i in range(0, 6, 2)]
            if True:
                for i in data:
                    sct_send(socket_client, int(i, 16))
    except KeyboardInterrupt:
        return 0

# check_ID()
# UART_read_write()
# cam_read(cam)
main()

# シリアルポート確認用
def check_ID():
    """
    ポートチェック
    """
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


# 以下テストに使用していたコード。

def UART_read_write():
    """
    serポートを定義、0.5sごとにUART_read()を呼ぶ。
    """
    ser = serial.Serial("COM3", 115200, timeout=5)
    try:
        while True:
            # UART_send(ser)
            # time.sleep(0.5)
            print("reading...")
            UART_read(ser)
    except KeyboardInterrupt:
        print("key interrupt detected")
        return 0
    

def cam_read(from_):
    """
    from_のカメラから読み、captureというウィンドウに表示
    """
    try:
        while True:
            ret, flame = from_.read()
            cv2.imshow("capture", flame)
            cam_capture_or_ret(flame)
    except KeyboardInterrupt:
        print("key interrupt detected")
        cv2.destroyAllWindows()


def cam_capture_or_ret(flame):
    """
    10msごとに、何か入力がないか確認する。
    """
    key = cv2.waitKey(10)
    if key == 13:
        cv2.imwrite("data/get_capture.png", flame)
    elif key == 27:
        cv2.destroyAllWindows()