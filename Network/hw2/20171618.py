import socket
import sys
import os
import time

# 웹 브라우저에 넣어야하는 URL 형식
# http://localhost:10000/biga.html

# 브라우저로 보내야하는 HTTP Response
# 존재하는 경우 200 OK // 존재하지 않는 경우 404 NOT FOUND를 보낸다


def HTTPResponse(contentLength, contecntType, booling):
    if booling:
        response = "HTTP/1.0 200 OK \r\n"
    else:
        response = "HTTP/1.0 404 NOT FOUND \r\n"
    response+= "Connection: close \r\n"
    response+= "ID: 20171618\r\n"
    response+= "Name: Seola Dong\r\n"
    response+= "Content-Length: "+contentLength+"\r\n"
    response+= "Content-Type: "+contecntType+"\r\n\r\n"
    return response


def runServer(PORT):
    # already = False
    while True:
        # 입력받은 PORT번호로 server를 만든다
        localhost = ('', PORT)
        try:
            RequestSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            RequestSocket.bind(localhost)
            # 브라우저가 요청을 바라는 메세지를 받는다
            RequestSocket.listen(5)
            conn, addr = RequestSocket.accept()
            # 한줄을 띄는 곳까지 받는다
            msg = b''
            while b'\r\n\r\n' not in msg:
                msg += conn.recv(1)
            msgRequest = msg.decode()

            print("Connection : Host IP ", addr[0], ", Port ", addr[1],
                  ", socket", str(conn).split('=')[1].split(" ")[0])
            print(msgRequest)

            # getReqest : 요청한 파일 이름 // getType : 요청한 파일의 타입
            getReqest = msgRequest.split("/")[1].split(" ")[0]
            getType = msgRequest.split("Accept: ")[1].split(',')[0]

            # 현재 이 코드가 존재하는 화일 경로 가저오기 ex) C: ~~/``/@@/###/20171618.py
            dirPath = os.getcwd()

            fileLen = 0
            findFile = ''
            booling = False
            # 현재 코드가 존재하는 화일 속에 있는 file 명 훑기
            for file in os.listdir(dirPath):
                fileLen += 1
                # 요청한 화일과 이름이 같은 화일 발견시 fileLen에 해당 화일의 바이트 크기를 넣음
                if file == getReqest:
                    findFile = file
                    fileLen = os.path.getsize(dirPath + "/" + file)
                    booling = True
                    break
                # 파일 속 모든 화일을 훑었는데 존재하지 않는다면 booling을 False로 한다
                if fileLen == len(os.listdir(dirPath)):
                    booling = False
                    break

            # 브라우저로 HTTP Response를 보낸다
            responseMsg = HTTPResponse(str(fileLen), getType, booling)
            responseMsg = responseMsg.encode()
            conn.send(responseMsg)

            # 요청한 화일을 찾지 못한경우 오류 메세지를 보낸다
            # 요청한 화일을 찾은 경우 해당 화일 정보를 보낸다
            if not (booling):
                print("Server Error : No such file ./", getReqest, "!")
            else:
                openFile = open(dirPath + "/" + findFile, 'r')
                sendLen = 0
                # 화일을 모두 읽어서 바이트로 바꾼후 보낸다
                while True:
                    line = openFile.readline()
                    if not line: break
                    encodingLine = line.encode()
                    conn.send(encodingLine)
                    sendLen += len(encodingLine)
                # 보낼꺼라고 예상한 화일정보크기랑 실제로 보낸 화일정보크기랑 같은지 확인
                # already = True
                print("finish ", fileLen, sendLen)

            # 요청사항이 담겨있던 소캣을 닫는다
            conn.close()
            # RequestSocket.close()
        except:
            continue

if __name__ == "__main__":
    print('Student ID : 20171618')
    print('Name : Seola Dong')
    PORT = int(sys.argv[1])
    time.sleep(1)
    while True:
        runServer(PORT)
        break
