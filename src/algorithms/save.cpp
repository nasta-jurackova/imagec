#include "save.hpp"

#include <QFileDialog>

namespace algorithms {
void save_image(Image& img, QString&) { 
	QString dest = QFileDialog::getSaveFileName(nullptr, "Select save destination", "", "Image (*.png)"); 
	if (dest.isEmpty())
        return;

	img.toQImage().save(dest);
}

} // namespace algorithms