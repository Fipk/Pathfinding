#pragma once

enum EditState
{
	Default,
	Start,
	End,
	Wall,
	CheckPoint

};

static const char* editStateName[] = { "Default", "Start", "End", "Wall", "CheckPoint"};