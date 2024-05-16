#include "BaseWindow.h"

BaseWindow::BaseWindow(Vec2 windowPos, Vec2 windowSize, double batuSize, double startTime)
	:m_window(windowPos,windowSize),
	m_batu(windowPos + Vec2(windowSize.x - batuSize, 0), batuSize),
	m_startTime(startTime)
{}

void BaseWindow::timeStart() {
	m_time.start();
}

void BaseWindow::move(double dt) {
	m_window.pos += m_vel * dt;
	m_batu.pos += m_vel * dt;
}

void BaseWindow::isClick() {
	if (m_batu.leftClicked()) {
		m_beClick = true;
	}
	else {
		m_beClick = false;
	}
}

void BaseWindow::isClickAd() {
	if (m_window.leftClicked()) {
		m_beClickAd = true;
	}
	else {
		m_beClickAd = false;
	}
}

bool BaseWindow::getIsClick() {
	return m_beClick;
}

void BaseWindow::actAdClick() {
	//未実装
}

void BaseWindow::update(double dt) {
	ClearPrint();
	if (m_startTime < m_time.sF()) {
		isClick();
		act();
		move(dt);
	}
	Print << m_time;

}

void BaseWindow::draw() {
	if (m_startTime < m_time.sF()) {

		switch (kind) {
		case AdKind::Anna:
			m_window.scaled(m_size)(v).draw(ColorF{1,1,1,m_opacity});
			break;
		case AdKind::Azarashi:
			m_window.scaled(m_size)(s).draw(ColorF{1,1,1,m_opacity});
			break;
		default:

			break;
		}
		m_batu.scaled(m_size).draw(ColorF{ 1,0,0,m_opacity });
	}

}

Stopwatch BaseWindow::m_time;
