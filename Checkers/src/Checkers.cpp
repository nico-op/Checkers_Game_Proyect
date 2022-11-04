/*
* Este es el archivo de programa principal de Checkers. La clase principal maneja selecciones de menú,
* las opciones del menú se seleccionan presionando la tecla correspondiente en el teclado.
* Todos los gráficos se dibujan utilizando primitivas SFML.
*/

#include "Checkers.hpp"
#include "CheckerGame.hpp"

using std::string;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::sort;

Checkers::Checkers() {}

/* En esta sección se inicia el juego  de Damas creando una ventana, opciones de menú y realizando una gráfica en la ventana */
void Checkers::start()
{
	const string RESOURCE_ERROR_IMAGE = "ERROR - cannot open \"resources/Checkerboard_8x8_125px.png\"";
	const string RESOURCE_ERROR_FONT = "ERROR - cannot open \"resources/ENGR.TTF\"";
	const string TITLE = "INMERSIVE CHECKERS";
	const string MAIN_MENU = "Para comenzar el juego utilice la letra 'C'\n"
		"Para ver las reglas utilice la letra 'R' \nPara observar el historial utilice la letra 'H'\n"
        "Para regresar al inicio utilice la letra 'B'";
	const string RULES = "See the Checker_Rules.txt files in resources.";
	const string VIEW_TIMES = "View Fastest Times (in minutes) selected, Main Screen";

    //Configuración de la ventana
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(WINDOW_POSITION_X, WINDOW_POSITION_Y));

    // Carga una imagen
	sf::Image image;
	if(!image.loadFromFile("/home/nico/Escritorio/ProyectoII_DatosII/Checkers/resources/Checkerboard_8x8_125px.png"))
		cerr << RESOURCE_ERROR_IMAGE << endl;
	// Vector out of range error
	//window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	
	// Carga el tipo de letra
	sf::Font font;
	if(!font.loadFromFile("/home/nico/Escritorio/ProyectoII_DatosII/Checkers/resources/Gayathri-Regular.otf"))
		cerr << RESOURCE_ERROR_FONT << endl;
	
	// Inicia las fuentes del menú
	sf::Text menuMessage, menuTitle;
	menuTitle.setFont(font);
	menuTitle.setCharacterSize(WINDOW_WIDTH / 40);
	menuTitle.setPosition(0, 0); //dibujar en la esquina superior izquierda de la ventana
	menuTitle.setColor(sf::Color::Red);
	menuTitle.setString(TITLE);
	menuMessage.setFont(font);
	menuMessage.setCharacterSize(WINDOW_WIDTH / 40);
	menuMessage.setPosition(0, WINDOW_HEIGHT / 40); // Dibujar debajo del titulo
	menuMessage.setColor(sf::Color::Black);
	menuMessage.setString(MAIN_MENU);
	
	int mouseOverX = 0, mouseOverY = 0; // se usa para recopilar información sobre los cables del mouse del usuario en la ventana
	
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if((event.type == sf::Event::Closed) 
				|| ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) // cerrar la ventana cuando esta en el menú
			{
				window.close();
			}

			else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::C)) // jugador versus computadora
			{
				CheckerGame checkerGame(window, true, false);
				checkerGame.startCheckers(window, event);
			}
			else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R)) // ver reglas
			{
				cout << RULES << endl;
			}
			else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::H)) // ver historial
			{
				cout << VIEW_TIMES << endl;
				loadTimes(window, event);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
                // guarda coordenadas y dibuja un cuadro verde o morado alrededor del cuadrado más cercano en el tablero de ajedrez.
				mouseOverX = event.mouseMove.x;
				mouseOverY = event.mouseMove.y;
			}
		}

        // Secuencia de dibujo de la ventana SFML
		window.clear(sf::Color::White);
		window.draw(menuTitle);
		window.draw(menuMessage);
		animation(window, mouseOverX, mouseOverY);
		window.display();
	}
}

/* carga las 10 puntuaciones más rápidas desde un almacenamiento de archivos externo */
void Checkers::loadTimes(sf::RenderWindow& window, sf::Event& event)
{
	const string RESOURCE_ERROR_SAV = "ERROR - cannot open \"game_times.sav\"";
	ifstream file("/home/nico/Escritorio/ProyectoII_DatosII/Checkers/src/game_times.sav"); // abre el archivo para lectura
	if(!file)
		cerr << RESOURCE_ERROR_SAV << endl;
	else
	{
		int i = 0;
		string temp;
		vector<string> times;
		times.push_back(temp);
		while(i < 10 && file >> temp)
		{
			++i;
			temp += "\n"; // agregar una nueva línea a la hora
			times.push_back(temp);
			// cout << temp << endl;
		}

        // carga la fuente del texto
		sf::Font font;
		if(!font.loadFromFile("/home/nico/Escritorio/ProyectoII_DatosII/Checkers/resources/ENGR.TTF"))
			cerr << "ERROR - cannot find resource file ENGR.TTF" << endl;
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(WINDOW_WIDTH / 40);
		text.setPosition(0, WINDOW_HEIGHT / 40); //dibujar ligeramente debajo del título
		text.setColor(sf::Color::Black);
        // ahora ordena los tiempos en orden no decreciente
		sort(times.begin(), times.end());
		// reset temp
		temp = "Utilice la letra B para volver al menu\n\n\n"
			"Top 10 Fastest Times:\n\n";
		vector<string>::const_iterator it;
		for(it = times.begin(); it != times.end(); ++it)
			temp += *it;
		// set the text to temp
		text.setString(temp);

		// este bucle mantiene las 10 mejores puntuaciones en la ventana
		bool view = true;
		while(view)
		{
			while(window.pollEvent(event))
			{
				// volver al menu
				if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::B))
				{
					cout << endl << "Closing Fastest Times View. Returning to Main Menu." << endl;
					view = false;
				}

                // Secuencia de dibujo SFML
				window.clear(sf::Color::White);
				window.draw(text); // dibuja los tiempos y el encabezado
				window.display();
			}
		}
	}
}

/* crea una pequeña animación que muestra el tablero en el menú principal */
void Checkers::animation(sf::RenderWindow& window, const int& mouseOverX, const int& mouseOverY)
{ 
	/* La animación es de un juego de damas simuladas. Ocupa aproximadamente 3/4 de la ventana */
    // restablecer sstartingstarting, y k
	int startingX = 0, startingY = WINDOW_HEIGHT / 4;
	sf::CircleShape circle (WINDOW_WIDTH / (2 * SQUARES_HORIZONTAL));
	circle.setPosition(WINDOW_WIDTH, 0); // deshacerse del círculo construido por defecto 0,0
	sf::RectangleShape square (sf::Vector2f(static_cast<float>(XOFFSET), static_cast<float>(YOFFSET)));
	for(int i = 0; i < SQUARES_VERTICAL - 2; ++i)
	{	
		for(int j = 0; j < SQUARES_HORIZONTAL; ++j)
		{
            // posicionar el cuadrado
			square.setPosition(static_cast<float>(startingX), static_cast<float>(startingY));
			sf::RectangleShape temp (sf::Vector2f(static_cast<float>(XOFFSET / 3), static_cast<float>(YOFFSET / 3)));
			temp.setPosition(static_cast<float>(mouseOverX), static_cast<float>(mouseOverY));
			if(square.getGlobalBounds().intersects(temp.getGlobalBounds()))
			{
                // le da al movimiento al cuadrado resaltado verde
				square.setOutlineThickness(-(SQUARES_VERTICAL / 2));
				square.setOutlineColor(sf::Color::Green);	
			}
			// create some random checkerpieces
			if(i <= 1 && !((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)))
			{
				circle.setFillColor(sf::Color::Black); //Pieza negra de animacion
				circle.setPosition(static_cast<float>(startingX), static_cast<float>(startingY));
			}
			else if(i >= 4 && !((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)))
			{
				circle.setFillColor(sf::Color::White); //Pieza blanca de animacion
				circle.setPosition(static_cast<float>(startingX), static_cast<float>(startingY));
			}

			if((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0))
				square.setFillColor(sf::Color(231,179,133)); //Color beige
			else
				square.setFillColor(sf::Color(92,37,0)); //Color cafe
			window.draw(square);
			window.draw(circle);
			startingX += XOFFSET;
            // borra cualquier resaltado de color anterior del cuadro
			square.setOutlineThickness(0);
			square.setOutlineColor(sf::Color(0, 0, 0, 255));
		}
		startingY += YOFFSET;
		startingX = 0;
	}
}