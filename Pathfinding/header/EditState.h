#pragma once

enum EditState
{
	Default,
	Start,
	End,
	Wall

};

static const char* editStateName[] = { "Default", "Start", "End", "Wall"};