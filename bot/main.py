import sys
import websocket
import threading
from json import dumps
import requests
from requests import utils
from json import loads
import os
from requests_toolbelt import MultipartEncoder

import bot

url = ''
username = ''
password = ''
listen_CID = 0


# init bot
B = bot.bot()

def on_open(ws):
    print('connect success!')


def on_error(ws, error):
    print(error)


def on_message(ws, json_data):
    data = loads(json_data)
    # print(data)
    # sleep(10)
    if data['type'] == 'push':
        print(data['body']['_CID'])
        if data['body']['event'] == 'ReceiveMsg' and data['body']['_CID'] == listen_CID:
            # Acquire message content when receive one
            body = {}
            body['_CID'] = listen_CID
            body['lastMsg_MID'] = 0
            body['num'] = 1
            data_send = {'cmd': 'get_messages', 'body': body}
            json_data_send = dumps(data_send)
            try:
                ws.send(json_data_send)
            except:
                print('connection is already closed.')
                sys.exit(0)
    elif data['type'] == 'response':
        if data['body']['code'] != 0:
            print('(something wrong!) ===>' + data['body']['msg'])
        else:
            if 'messages' in data['body'] and data['body']['messages'][0]['direction'] == 'In':
                for elem in data['body']['messages'][0]['segments']:
                    if elem['type'] == 'plaintext':
                        # Call bot for answer and send the answer
                        answer = B.speak(elem['content']['text'])
                        message_content = {}
                        message_content['text'] = answer
                        message_segment = {}
                        message_segment['type'] = 'plaintext'
                        message_segment['content'] = message_content
                        message = {}
                        message['segments'] = [message_segment]
                        segments = []
                        segments.append(message)
                        body = {}
                        body['_CID'] = listen_CID
                        body['message'] = message
                        data_send = {'cmd': 'post_message', 'body': body}
                        json_data_send = dumps(data_send)
                        try:
                            ws.send(json_data_send)
                        except:
                            print('connection is already closed.')
                            sys.exit(0)



def on_close(ws, close_status_code, close_msg):
    if close_status_code or close_msg:
        print('close status code:', close_status_code)
        print('close msg:', close_msg)
    try:
        print(">>>>>>CLOSED")
        os._exit(0)
    except:
        pass


# login
url_connect = 'http://' + url + '/login'
play_load = {'username': username, 'password': password}
play_load_from_data = MultipartEncoder(play_load)
headers = {'Content-Type': play_load_from_data.content_type}
r = requests.post(url_connect, data=play_load_from_data, headers=headers)
print('connecting to {}'.format(url_connect))
if r.status_code != 200:
    print('登录失败，原因：{}'.format(r.reason))
    exit()
else:
    print('request success!')
cookies_dic = requests.utils.dict_from_cookiejar(r.cookies)
print(cookies_dic)
cookie_str = ''
for key in cookies_dic:
    cookie_str += key + '=' + cookies_dic[key] + ';'
cookie_str = cookie_str.strip(';')

# connect
ws_app = websocket.WebSocketApp('ws://' + url + '/app',
                                on_open=on_open, on_message=on_message,
                                on_close=on_close, on_error=on_error, cookie=cookie_str)
ws_app.run_forever()
