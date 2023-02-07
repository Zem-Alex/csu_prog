#include "Header.hpp"

using namespace std;

const int WEIGHT = 600;
const int HEIGHT = 400;

sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Alarm");

int main()
{
    int inHours, inMinutes, inSeconds, systemHours, systemMinutes, systemSeconds, hoursLeft, minutesLeft, secondsLeft;
    bool timeOver = true;
    char hourMass[2], minMass[2], secMass[2], inputStr[9];

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    Textbox text1(20, sf::Color::Black, true);
    text1.setPosition({ 400, 100 });
    text1.setLimit(true, 8);
    text1.setFont(font);

    Button btn1("Start/stop timer", { 300, 100 }, 30, sf::Color(128,128,128), sf::Color::Black);
    btn1.setFont(font);
    btn1.setPosition({ 100, 300 });

    sf::Text textSysTime, textInTime, textLeftTime;
    ostringstream textSysTimeString, textInTimeString, textLeftTimeString;

    textSysTime.setFont(font); // font is a sf::Font
    textSysTime.setPosition({ 0, 100 });
    textSysTime.setCharacterSize(24); // in pixels, not points!

    textSysTime.setFillColor(sf::Color::Yellow);
    textSysTime.setOutlineColor(sf::Color::Black);
    textSysTime.setOutlineThickness(3);

    textInTime.setFont(font); // font is a sf::Font
    textInTime.setPosition({ 0, 0 });
    textInTime.setCharacterSize(24); // in pixels, not points!

    textInTime.setFillColor(sf::Color::White);
    textInTime.setOutlineColor(sf::Color::Black);
    textInTime.setOutlineThickness(3);

    textLeftTime.setFont(font); // font is a sf::Font
    textLeftTime.setPosition({ 0, 200 });
    textLeftTime.setCharacterSize(24); // in pixels, not points!

    textLeftTime.setFillColor(sf::Color::Red);
    textLeftTime.setOutlineColor(sf::Color::Black);
    textLeftTime.setOutlineThickness(3);

    SYSTEMTIME st;
    setlocale(LC_ALL, "");

    bool flag = false;
    while (timeOver)
    {
        sf::Event Event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            text1.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            text1.setSelected(false);
        }
        while (window.pollEvent(Event)) {
            switch (Event.type) {

            case sf::Event::Closed:
                window.close();
            case sf::Event::TextEntered:
                text1.typedOn(Event);
            case sf::Event::MouseMoved:
                if (btn1.isMouseOver(window)) {
                    btn1.setBackColor(sf::Color(158, 158, 158));
                }
                else {
                    btn1.setBackColor(sf::Color(128,128,128));
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (btn1.isMouseOver(window)) {
                    //std::cout << text1.getText() << "\n";
                    hourMass[0] = text1.getText()[0];
                    hourMass[1] = text1.getText()[1];
                    minMass[0] = text1.getText()[3];
                    minMass[1] = text1.getText()[4];
                    secMass[0] = text1.getText()[6];
                    secMass[1] = text1.getText()[7];
                    inHours = atoi(hourMass);
                    inMinutes = atoi(minMass);
                    inSeconds = atoi(secMass);
                    flag = !flag;
                }
            }
        }
        window.clear(sf::Color(188,188,188));

        GetSystemTime(&st);
        systemHours = st.wHour + 5;
        systemMinutes = st.wMinute;
        systemSeconds = st.wSecond;

        textSysTimeString.str("");
        textSysTimeString.clear();
        textSysTimeString << systemHours << " : " << systemMinutes << " : " << systemSeconds;
        textSysTime.setString("System time: " + textSysTimeString.str());
        window.draw(textSysTime);

        sf::RectangleShape rectangle(sf::Vector2f(100, 40));

        // меняем размер 100x100
        rectangle.setPosition(sf::Vector2f(395, 95));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color::Black);
        window.draw(rectangle);

        if (flag)
        {
            hoursLeft = inHours + 24 - systemHours;
            minutesLeft = inMinutes - systemMinutes;
            secondsLeft = inSeconds - systemSeconds;

            if (secondsLeft < 0)
            {
                minutesLeft--;
                secondsLeft += 60;
            }
            if (minutesLeft < 0)
            {
                hoursLeft--;
                minutesLeft += 60;
            }
            if (hoursLeft > 23)
                hoursLeft -= 24;


            if (inHours == systemHours && inMinutes == systemMinutes && inSeconds == systemSeconds)
                timeOver = false;

            textInTimeString.str("");
            textInTimeString.clear();
            textInTimeString << inHours << " : " << inMinutes << " : " << inSeconds;
            textInTime.setString("Entered time: " + textInTimeString.str());
            window.draw(textInTime);

            textLeftTimeString.str("");
            textLeftTimeString.clear();
            textLeftTimeString << hoursLeft << " : " << minutesLeft << " : " << secondsLeft;
            textLeftTime.setString("Time left: " + textLeftTimeString.str());
            window.draw(textLeftTime);
        }

        text1.drawTo(window);
        btn1.drawTo(window);
        window.display();
    }

    while (!_kbhit())
    {
        cout << '\a';
        Sleep(2000);
    }

    return 0;
}