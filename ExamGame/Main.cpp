#include <set>
#include <Siv3D.hpp>
#include "button.hpp"
#include "problem.hpp"

Array<String>pnames;

Array<Problem>probs;
Array<int>orders;

void init() {
	probs.clear();
	String str;
	int res = 0;
	std::set<String>already;
	Array<String>names;
	for (auto g : pnames) names.push_back(g);
	pnames.clear();
	for (int _ = 0; _ < names.size(); _++) {
		auto filename = names[_];
		if (filename == U"") continue;
		if (already.find(filename) != already.end()) continue;
		already.insert(filename);
		CSVData csv(U"Probs/" + filename + U".csv");
		if (!csv) {
			TextReader read(U"Probs/" + filename + U".txt");
			if (!read) continue;
			String line;
			while (read.readLine(line)) {
				names.push_back(line);
			}
			continue;
		}
		else pnames.push_back(filename);
	}
	for (int _ = 0; _ < pnames.size(); _++) {
		auto filename = pnames[_];
		CSVData csv(U"Probs/" + filename + U".csv");
		Array<bool>vailds;
		TextReader reader(U"Probs/Datas/" + filename + U".txt");
		while (reader.readLine(str)) {
			vailds << Parse<int>(str);
		}
		for (int i = 0; i < csv.rows(); i++) {
			if (i < vailds.size()) {
				probs << Problem(csv[i][0], csv[i][1], vailds[i], filename, i);
				psize++;
			}
			else {
				probs << Problem(csv[i][0], csv[i][1], 1, filename, i);
				psize++;
			}
		}
	}
}
void Select(int &num) {
	if (psize == 0) return;
	num = Random(probs.size() - 1);
	while (!probs[num].valid) {
		num = Random(probs.size());
	}
}

void drawProb(String& s,int top, Font& font) {
	for (int i = 0; i < s.size(); i += 20) {
		String tmp = U"";
		for (int j = i; j < s.size() && j < i + 20; j++) {
			tmp += s[j];
		}
		font(tmp).drawAt(Scene::Center().x, top + (i / 20) * 38, Palette::Black);
	}
}

void Main() {
	Window::SetTitle(U"CrammingGame");
	Window::Resize(800, 600);
	Scene::SetBackground(Palette::Thistle);
	Font probFont(30);
	bool pre_mouse = 0;
	int num;
	int probnum = 0;
	int probsize = 0;
	int number = 0;
	Button OKButton(Rect(150, 450, 500, 100), Palette::Blue, 50, U"OK!", 1);
	Button neverButton(Rect(100, 450, 250, 100), Palette::Blue, 50, U"never", 1);
	Button nextButton(Rect(450, 450, 250, 100), Palette::Blue, 50, U"NEXT", 1);
	int mode = 0;
	//
	//0=タイトル画面
	Font Title(80);
	Button start(Rect(150, 450, 500, 100), Palette::Black, 80, U"Start!", 1);
	//1=問題選択画面 どのテキストファイル、何問
	Font setFont(40);
	String quest;
	Font pFont(20);
	Rect area(120, 340, 560, 80);
	//2=出題画面
	//3=答えが見られるよ
	//4=リザルト画面
	bool probfirst = 1, pfirst2, randomize = 0;
	String revtext = U"Not Reverse?";
	while (System::Update())
	{
		if (scene == 0) {
			Title(U"CrammmingGame").drawAt(Scene::CenterF().x, 100, Palette::Gold);
			Title(U"Ver 2.1.0").drawAt(Scene::CenterF().x, 190, Palette::Gold);
			start.draw();
			if (KeyT.pressed() && KeyH.pressed() && KeyI.pressed() && KeyS.pressed()) {
				Scene::SetBackground(Palette::Gold);
				revtext = U"Ushitapunichia";
			}
			if (KeyEnter.down() || (!pre_mouse && start.onclick())) {
				scene = 1;
			}
		}
		else if (scene == 1) {
			Title(U"Settings").drawAt(Scene::CenterF().x, 50);
			SimpleGUI::CheckBox(probfirst, revtext, Vec2(500, 135));
			SimpleGUI::CheckBox(randomize, U"Randomize?", Vec2(500, 175));

			setFont(U"File names").drawAt(200, 300);
			area.draw(Palette::White);
			pFont(quest).draw(area.stretched(-20), Palette::Black);

			start.draw();
			bool enterdown = KeyEnter.down();
			if (enterdown || (!pre_mouse && start.onclick())) {
				if (quest.size() == 0) {
					pnames << U"Probs";
				}
				else {
					pnames = quest.split(',');
				}
				scene = 2;
				init();

				for (auto g : probs) {
					if (g.valid) probsize++;
				}
				for (int i = 0; i < probs.size(); i++) orders << i;
			
				orders.shuffle();
				pfirst2 = probfirst;
				if (probsize == 0) goto end;
				while (1) {
					if (probnum == psize) {
						orders.shuffle();
						probnum = 0;
						continue;
					}
					num = orders[probnum];
					if (!probs[num].valid) {
						probnum++;
						continue;
					}
					break;
				}
			}
			if (!KeyEnter.pressed()) TextInput::UpdateText(quest);
		loop:;
		}
		else if (scene == 2) {
			drawProb(pfirst2 ? probs[num].prob : probs[num].ans, 100, probFont);
			pFont(Format(probsize) + U" problems remain").drawAt(Scene::Center().x, 55);
			pFont(Format((int)Scene::Time() / 60) + U"' " + Format((int)Scene::Time() % 60) + U"''  have passed").draw(50, 40);
			SimpleGUI::CheckBox(probfirst, revtext, Vec2(580, 5));
			SimpleGUI::CheckBox(randomize, U"Randomize?", Vec2(580, 45));
			OKButton.draw();
			if (KeyEnter.down() || (!pre_mouse && OKButton.onclick())) {
				scene = 3;
			}
		}
		else if (scene == 3) {
			SimpleGUI::CheckBox(probfirst, revtext, Vec2(580, 5));
			SimpleGUI::CheckBox(randomize, U"Randomize?", Vec2(580, 45));
			drawProb(pfirst2 ? probs[num].prob : probs[num].ans, 100, probFont);
			drawProb(pfirst2 ? probs[num].ans : probs[num].prob, 300, probFont);
			pFont(Format(probsize) + U" problems remain").drawAt(Scene::Center().x, 55);
			pFont(Format((int)Scene::Time() / 60) + U"' " + Format((int)Scene::Time() % 60) + U"''  have passed").draw(50, 40);
			neverButton.draw();
			nextButton.draw();
			if (KeyBackspace.down() || (!pre_mouse && neverButton.onclick())) {
				probs[num].del();
			}
			if (KeyEnter.down() || (!pre_mouse && nextButton.onclick())) {
				if (!probs[num].valid) probsize--;
				if (probsize == 0) goto end;
				probnum++;
				number++;
				while (1) {
					if (probnum == probs.size()) {
						orders.shuffle();
						probnum = 0;
						continue;
					}
					num = orders[probnum];
					if (!probs[num].valid) {
						probnum++;
						continue;
					}
					break;
				}
				scene = 2;
				pfirst2 = probfirst;
				if (randomize) {
					pfirst2 = RandomBool();
				}
			}
			if (probs[num].valid == 0) {
				Circle(50, 500, 20).draw(Palette::Red);
			}
		}
		pre_mouse = MouseL.pressed();
	}
end:;
	int res = 0;
	for (auto filename : pnames) {
		CSVData csv(U"Probs/" + filename + U".csv");
		if (!csv) continue;
		TextWriter writer(U"Probs/Datas/" + filename + U".txt");
		for (int i = 0; i < csv.rows(); i++) {
			if (probs[res++].valid) {
				writer.writeln(U"1");
			}
			else {
				writer.writeln(U"0");
			}
		}
	}
}