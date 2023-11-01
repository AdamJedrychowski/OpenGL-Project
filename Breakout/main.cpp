#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
	// Setup ImGui context
	ImGui::CreateContext();
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test GUI");
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) { window.close(); }
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Test Begin");
                ImGui::Button("Test Button");
		ImGui::End();

		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	} //end while

	ImGui::SFML::Shutdown();
}