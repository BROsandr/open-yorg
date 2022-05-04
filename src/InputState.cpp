#include "InputState.hpp"

InputState::InputState(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_, Input &input) : interface {interface}, pathSearchField {pathSearchField}, field{field}, enemies{ enemies }, bullets{bullets}, damageCircles{damageCircles_}, resourceBalls{resourceBalls_}, road{road_}, input {input}{}
