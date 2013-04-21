
#ifndef _COLORUTILS_H_
#define _COLORUTILS_H_

#include <QString>

#ifndef Q_OS_WIN
#define COLOR_OUTPUT_SUPPORT 1
#endif

class QWidget;
class QColor;

class ColorUtils {

public:

	//! Returns a string suitable to be used for -ass-color
	static QString colorToRRGGBBAA(unsigned int color);
	static QString colorToRRGGBB(unsigned int color);

	//! Returns a string suitable to be used for -colorkey
	static QString colorToRGB(unsigned int color);

	static QString colorToAABBGGRR(unsigned int color);

	//! Changes the foreground color of the specified widget
	static void setForegroundColor(QWidget * w, const QColor & color);

	//! Changes the background color of the specified widget
	static void setBackgroundColor(QWidget * w, const QColor & color);

    /**
     ** \brief Strip colors and tags from MPlayer output lines
     **
     ** Some MPlayer configurations (configured with --enable-color-console)
     ** use colored/tagged console output. This function removes those colors
     ** and tags.
     **
     ** \param s The string to strip colors and tags from
     ** \return Returns a clean string (no colors, no tags)
     */
#if COLOR_OUTPUT_SUPPORT
    static QString stripColorsTags(QString s);
#endif

};

#endif
