#pragma once

#include "Graphics.h"
#include "Sound.h"

class MemeField {
private:
	class Tile {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
		void Draw(const Vei2& screenPos, bool fucked, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		void SetNeighborMemeCount(int memeCount);
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	MemeField(const Vei2& center, int nMemes);
	void Draw(Graphics& gfx) const;
	RectI GetRect() const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
	bool GameIsWon() const;
	bool GameIsLost() const;
private:
	MemeField::Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos);
	int CountNeighborMemes(const Vei2& gridPos);
private:
	static constexpr int width = 4;
	static constexpr int height = 3;
	static constexpr int borderThickness = 10;
	static constexpr Color borderColor = Colors::Blue;
	Sound sndLose = Sound(L"spayed.wav");
	Vei2 topLeft;
	bool isFucked = false;
	Tile field[width * height];
};