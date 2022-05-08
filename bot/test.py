import bot

a = bot.bot()
while True:
    s = input()
    s = a.speak(s)
    print(s)