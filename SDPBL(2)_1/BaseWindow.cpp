#include "BaseWindow.h"

BaseWindow::BaseWindow(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	:m_window(windowPos, windowSize),
	m_batu(windowPos + Vec2(windowSize.x - batuSize, 0), batuSize),
	m_startTime(startTime),
	resourcePath(Resource(U"video/christmas.mp4")),
	temporaryFilePath(FileSystem::TemporaryDirectoryPath() + U"MyApp/christmas.mp4"),
	christmas(LoadVideoFromResource(resourcePath, temporaryFilePath, Loop::Yes))
{}

void BaseWindow::timeReset() {
	m_timeS.reset();
}

void BaseWindow::timeStart() {
	m_timeS.start();
}

void BaseWindow::timeStop() {
	m_timeS.pause();
}

void BaseWindow::move(double dt) {
	m_window.pos += m_vel * dt;
	m_batu.pos += m_vel * dt;
}

void BaseWindow::isClick() {
	if (m_batu.leftClicked()) {
		m_beClick = true;
		m_AllBatuNotClicked = false;
	}
	else {
		m_beClick = false;
	}
}

void BaseWindow::isClickAd() {
	if (m_window.leftClicked() && !m_beClick && m_AllBatuNotClicked) {
		m_beClickAd = true;
	}
	else {
		m_beClickAd = false;
	}
}

bool BaseWindow::getIsClicked() {
	return m_beClick;
}

bool BaseWindow::getIsClickedAd() {
	return m_beClickAd;
}

bool BaseWindow::getIsNotAllClicked() {
	return m_AllBatuNotClicked;
}

void BaseWindow::SetNotAllClicked() {
	m_AllBatuNotClicked = true;
}

void BaseWindow::actAdClick() {
	//未実装
}

void BaseWindow::setPopKind() {
	if (m_beClickAd == true) {
		kindPop = kind;
	}
}

AdKind BaseWindow::getKindPop() {
	return kindPop;
}

MoveKind BaseWindow::getMoveKind() {
	return moveKind;
}

double BaseWindow::getTime() {
	return m_time.sF();
}

void BaseWindow::flagFreqT() {
	flagFreq = true;
}

bool BaseWindow::getFlagFreq() {
	return flagFreq;
}

void BaseWindow::update(double dt) {
	//Print << U"m_startTime=" << m_startTime;
	
	if (m_startTime < m_timeS.sF()) {

		if (!flagTimer) {
			m_time.start();
			flagTimer = true;
		}

		isClick();
		isClickAd();
		setPopKind();
		act();	
		move(dt);
		//move_batu(dt);
	}
	//Print << m_AllBatuNotClicked;
	//Print << m_timeS;
	//Print << (int)AdKind();
}

void BaseWindow::draw() {
	//Print << U"m_startTime < m_timeS.sF()=" << (m_startTime < m_timeS.sF());
	//Print << m_startTime;
	//Print << m_timeS.sF();
	if (m_startTime < m_timeS.sF()) {
		
		switch (kind) {
		case AdKind::Anna:
			m_window.scaled(m_size)(TextureAsset(U"Anna")).draw(ColorF{1,1,1,m_opacity});
			break;
		case AdKind::Azarashi:
			m_window.scaled(m_size)(TextureAsset(U"Azarashi")).draw(ColorF{1,1,1,m_opacity});
			break;
		case AdKind::BatuDarake:
			m_window.scaled(m_size)(TextureAsset(U"BatuDarake")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::Building:
			m_window.scaled(m_size)(TextureAsset(U"Building")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::Car:
			m_window.scaled(m_size)(TextureAsset(U"Car")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::Christmas:
			christmas.advance();
			m_window.scaled(m_size)(christmas).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::Hair:
			m_window.scaled(m_size)(TextureAsset(U"Hair")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::MatchingApp:
			m_window.scaled(m_size)(TextureAsset(U"MatchingApp")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		case AdKind::QuickCatch:
			m_window.scaled(m_size)(TextureAsset(U"QuickCatch")).draw(ColorF{ 1,1,1,m_opacity });
			break;
		default:
			break;
		}
		//m_batu.scaled(m_size).draw(ColorF{ 1,0,0,m_opacity });
		//TextureAsset(U"Batu").scaled(0.5).drawAt(m_window.x + m_window.w - TextureAsset(U"Batu").size().x, m_window.y + TextureAsset(U"Batu").size().y);

		if (moveKind == MoveKind::BatuMove) {
			TextureAsset(U"Batu").scaled(batuScaleG).drawAt(m_batu.x + m_batu.w/2 , m_batu.y + m_batu.h/2 , ColorF(1, 1, 1, m_opacity));
		}
		else{
			TextureAsset(U"Batu").scaled(batuScaleG).draw(m_window.x + m_window.w - TextureAsset(U"Batu").size().x * batuScaleG, m_window.y, ColorF(1, 1, 1, m_opacity));
		}

	}
}

void BaseWindow::drawPop(double dt) {
	//m_opacityP += 1*dt;
	m_opacityP = 1;
	switch (kindPop) {
	case AdKind::Anna:
		TextureAsset(U"Anna").scaled(1).drawAt(Scene::Center(), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::Azarashi:
		TextureAsset(U"Azarashi").scaled(0.44).drawAt(Scene::Center() + Vec2(0, 33), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::BatuDarake:
		TextureAsset(U"BatuDarake").scaled(0.28).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::Building:
		TextureAsset(U"Building").scaled(0.195).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::Car:
		TextureAsset(U"Car").scaled(0.505).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::Christmas:
		/*VideoTextureAssetをstaticにできないためGameで描画しています...*/
		//christmas.advance();
		//christmas.drawAt(Scene::Center());
		break;
	case AdKind::Hair:
		TextureAsset(U"Hair").scaled(0.57).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::MatchingApp:
		TextureAsset(U"MatchingApp").scaled(0.305).drawAt(Scene::Center() + Vec2(0, 34), ColorF(1, 1, 1, m_opacityP));
		break;
	case AdKind::QuickCatch:
		TextureAsset(U"QuickCatch").scaled(0.97).drawAt(Scene::Center() + Vec2(0, 35), ColorF(1, 1, 1, m_opacityP));
		break;
	default:
		break;
	}
}

Stopwatch BaseWindow::m_timeS;
bool BaseWindow::m_AllBatuNotClicked = true;
AdKind BaseWindow::kindPop=AdKind::Anna;
double BaseWindow::m_opacityP=0;
