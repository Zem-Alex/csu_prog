import telebot
import requests
from ipinfo import getHandler

# Замените YOUR_BOT_TOKEN на токен вашего бота
TOKEN = '6500830549:AAGZqJ2JEdXbuEck7GzY7-4fnT_NJ785GmI'
# Замените YOUR_IPINFO_TOKEN на ваш API-ключ для ipinfo.io
IPINFO_TOKEN = 'd4d27cbf7fe3b3'

# Создаем объект бота
bot = telebot.TeleBot(TOKEN)

# Обработчик команды /start
@bot.message_handler(commands=['start'])
def start(message):
    bot.send_message(message.chat.id, "Привет! Я бот, который предоставляет информацию о пользователе по IP-адресу. Просто отправьте мне IP-адрес.")

# Обработчик текстовых сообщений
@bot.message_handler(func=lambda message: True)
def get_user_info(message):
    ip_address = message.text
    try:
        user_info = get_user_info_by_ip(ip_address)
        bot.send_message(message.chat.id, user_info)
    except Exception as e:
        bot.send_message(message.chat.id, f"Произошла ошибка: {str(e)}. Пожалуйста, убедитесь, что введен корректный IP-адрес.")

# Получение информации о пользователе по IP-адресу
def get_user_info_by_ip(ip_address):
    handler = getHandler(IPINFO_TOKEN)
    details = handler.getDetails(ip_address)
    country = details.country
    city = details.city
    latitude = details.latitude
    longitude = details.longitude
    return f"Страна: {country}\nГород: {city}\nКоординаты: {latitude}, {longitude}"

if __name__ == '__main__':
    bot.polling(none_stop=True)
