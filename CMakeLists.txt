cmake_minimum_required(VERSION 3.10)
project(rtype)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

else ()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -W -Wall -Wextra -Wno-missing-field-initializers -Wno-unused-parameter")
endif ()


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(Client/)
include_directories(Common/GameEngine)
include_directories(Client/src/game)
include_directories(Client/includes)


set(COMMONS_SRCS
	Common/WindowsCtor.cpp
	Common/WindowsCtor.hpp

	Common/Network/EndpointBase.hpp
	Common/Network/GameProtocol.hpp

	Common/Network/TcpSocket/ATcpSocket.hpp
	Common/Network/TcpSocket/TcpSocket.hpp
	Common/Network/TcpSocket/CommonTcpSocket.cpp
	Common/Network/TcpSocket/Unix/UnixTcpSocket.cpp
	Common/Network/TcpSocket/Unix/UnixTcpSocket.hpp
	Common/Network/TcpSocket/Windows/WindowsTcpSocket.cpp
	Common/Network/TcpSocket/Windows/WindowsTcpSocket.hpp

	Common/Network/UdpSocket/UdpSocket.hpp
	Common/Network/UdpSocket/UdpSocket.cpp

	Common/Opts/Opts.cpp
	Common/Opts/Opts.hpp

	Common/Json/Entity.hpp
	Common/Json/Parser.hpp
	Common/Json/src/Entity.cpp
	Common/Json/src/Parser.cpp

	Common/JsonBuilder/JsonBuilder.hpp
	Common/JsonBuilder/JsonBuilder.cpp

	Common/Event/Event.hpp
	Common/Event/Event.tpp
	Common/Event/Manager.hpp
	Common/Event/Manager.tpp
	Common/Event/HdlCollector.hpp
	Common/Event/src/Event.cpp
	Common/Event/src/HdlCollector.cpp
)

set(ECS_GRAPHICS
	Common/GameEngine/component/graphical/AnimatedSprite.hpp
	Common/GameEngine/component/graphical/AnimatedSpriteMap.hpp
	Common/GameEngine/component/graphical/Sprite.hpp
	Common/GameEngine/system/graphical/Graphicals.cpp
	Common/GameEngine/system/graphical/Graphicals.hpp
	Common/GameEngine/component/graphical/Drawable.hpp
)

set(ECS_PHYSIC
	Common/GameEngine/component/physic/Position.hpp
	Common/GameEngine/component/physic/Speed.hpp
	Common/GameEngine/component/physic/Acceleration.hpp
	Common/GameEngine/system/physic/Speeds.cpp
	Common/GameEngine/system/physic/Speeds.hpp
	Common/GameEngine/system/physic/Acceleration.cpp
	Common/GameEngine/system/physic/Acceleration.hpp
	Common/GameEngine/component/physic/Hitbox.hpp
)

set(ECS_CORE
	Common/GameEngine/ecs/Ecs.hpp
	Common/GameEngine/ecs/Entity.cpp
	Common/GameEngine/ecs/Entity.hpp
	Common/GameEngine/ecs/ListComponent.hpp
	Common/GameEngine/ecs/DataBank.hpp

	Common/GameEngine/core/CoreVector.hpp
	Common/GameEngine/core/Time.cpp
	Common/GameEngine/core/Time.hpp
)

set(ECS_SFML
	Common/GameEngine/sfml/Graphic.cpp
	Common/GameEngine/sfml/Graphic.hpp

	Common/GameEngine/component/audio/Sound.hpp
	Common/GameEngine/system/control/ControlsSFML.hpp
	Common/GameEngine/system/control/ControlsSFML.cpp
)

set(ECS_CONTROLS
	Common/GameEngine/component/control/Keyboard.hpp
	Common/GameEngine/component/control/Mouse.hpp
	Common/GameEngine/component/control/Controller.hpp
	Common/GameEngine/component/control/LazyDeplacementMouse.hpp
	Common/GameEngine/component/control/DeplacementKeyBoard.hpp
	Common/GameEngine/component/control/DeplacementMouse.hpp
	Common/GameEngine/system/control/Controls.cpp
	Common/GameEngine/system/control/Controls.hpp)


add_executable(rtype
	${COMMONS_SRCS}

	${ECS_GRAPHICS}
	${ECS_PHYSIC}
	${ECS_CORE}
	${ECS_SFML}
	${ECS_CONTROLS}

	Client/lib/TimedEvent/TimedEvent.cpp
	Client/lib/TimedEvent/TimedEvent.hpp
	Client/lib/TimedEvent/TimedEventAdmin.cpp
	Client/lib/TimedEvent/TimedEventAdmin.hpp

	Client/src/game/component/ai.hpp
	Client/src/game/enemy/enemy1/enemy1.hpp
	Client/src/game/enemy/enemy1/enemy1.cpp
	Client/src/game/enemy/enemy2/enemy2.hpp
	Client/src/game/enemy/enemy2/enemy2.cpp
	Client/src/game/enemy/enemy3/enemy3.hpp
	Client/src/game/enemy/enemy3/enemy3.cpp
	Client/src/game/system/ai.cpp
	Client/src/game/system/ai.hpp
	Client/src/game/system/Fire.cpp
	Client/src/game/system/Fire.hpp
	Client/src/game/system/Bonuses.cpp
	Client/src/game/system/walls.cpp
	Client/src/game/system/gen.cpp
	Client/src/game/enemy/enemy.hpp

	Client/includes/ServerConnection.hpp
	Client/src/ServerConnection.cpp

	Client/includes/MessageBox.hpp

	Client/src/game/component/Parallax.hpp
	Client/src/game/system/Parallaxs.hpp
	Client/src/game/system/Parallaxs.cpp

	Client/includes/Game.hpp
	Client/src/Game.cpp
	Client/src/game/menu/Menu.hpp

	Client/src/Main.cpp
	Common/GameEngine/component/online/OnlineComponent.hpp)

find_package (Threads)
target_link_libraries(rtype ${CONAN_LIBS})
target_link_libraries(rtype ${CMAKE_THREAD_LIBS_INIT})


project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Server)
include_directories(Server/src)
include_directories(Server/includes)
include_directories(Common)

add_executable(server
	${COMMONS_SRCS}

	${ECS_PHYSIC}
	${ECS_CORE}
	${ECS_CONTROLS}

	Server/src/Main.cpp

	Server/includes/Server.hpp
	Server/src/Server.cpp

	Server/includes/ClientConnection.hpp
	Server/src/ClientConnection.cpp

	Server/includes/TcpListener.hpp
	Server/includes/TcpListenerSlave.hpp
	Server/includes/TcpListener.tpp

	Server/includes/Router.hpp
	Server/src/Router.cpp

	Server/includes/Session/Manager.hpp
	Server/src/Session/Manager.cpp
	Server/includes/Session/Session.hpp
	Server/src/Session/Session.cpp
	Server/includes/Session/Game.hpp
	Server/src/Session/Game.cpp

	Server/src/Session/components/ai.hpp
	Server/src/Session/enemy/enemy1/enemy1.hpp
	Server/src/Session/enemy/enemy1/enemy1.cpp
	Server/src/Session/enemy/enemy2/enemy2.hpp
	Server/src/Session/enemy/enemy2/enemy2.cpp
	Server/src/Session/systems/ai.cpp
	Server/src/Session/systems/ai.hpp
	Server/src/Session/systems/Fire.cpp
	Server/src/Session/systems/Fire.hpp
	Server/src/Session/systems/gen.cpp
	Server/src/Session/enemy/enemy.hpp
	
	Server/src/Session/TimedEvent/TimedEvent.cpp
	Server/src/Session/TimedEvent/TimedEvent.hpp
	Server/src/Session/TimedEvent/TimedEventAdmin.cpp
	Server/src/Session/TimedEvent/TimedEventAdmin.hpp
)

target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
