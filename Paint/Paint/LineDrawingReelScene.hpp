# include <Siv3D.hpp> // Siv3D v0.6.12


class LineDrawingReelScene {
public:
	// コンストラクタで線画をTextureにしてセット
	LineDrawingReelScene(void);
	void draw(void) const;
private:
	Array<Texture> textures;
	double move_speed = 10.0;
	double move_time = 5.0;
};
