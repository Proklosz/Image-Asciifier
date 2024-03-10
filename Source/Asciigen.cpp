#include <gtkmm.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Gtk;
using namespace cv;

class MainWindow : public Window {
public:
  MainWindow();
  virtual ~MainWindow();

private:
  VBox vbox;
  HBox TargetReshbox, charsHbox;
  Label label;
  Entry entry;
  Button button;
  Label resultImage;
  Button copy_button;
  Button Ascify_button;
  Button AddCharButton;
  Button Defult;

  std::string filename;
  string res;
  int shadeNum = 5;
  std::vector<string> shade = {"⠀", "░", "▒", "▓", "█"};

  void on_copy_button_clicked(Gtk::Label &label);
  void on_button_clicked();
  void Ascify(string filename);
  void on_ascify_button_clicked();
  void on_ADD_Char();
  void on_DELETE_Char(Entry *entryToRemove);
  void on_Def();

  vector<Label *> IndexLabel_list;
  vector<Entry *> ChartoDraw_list;
  vector<Button *> Remove_list;
};

MainWindow::MainWindow() {
  set_title("ASCII Image Generator");
  set_default_size(10, 10);
  set_size_request(10, 10);

  vbox.set_name("vbox");
  add(vbox);

  vbox.pack_start(charsHbox, PACK_SHRINK);
  charsHbox.set_name("chb");

  Defult.set_label("Default");
  Defult.set_name("chb");
  Defult.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_Def));
  charsHbox.pack_end(Defult, PACK_SHRINK);

  AddCharButton.set_label("+Add character");
  AddCharButton.set_name("ACB");
  AddCharButton.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::on_ADD_Char));
  charsHbox.pack_end(AddCharButton, PACK_SHRINK);

  for (int i = 0; i < shadeNum; i++) {
    on_ADD_Char();
    ChartoDraw_list[i]->set_text(shade[i]);
  }

  TargetReshbox.set_homogeneous(true);
  vbox.pack_start(TargetReshbox, PACK_SHRINK);

  label.set_label("Target Width:");
  TargetReshbox.pack_start(label, PACK_SHRINK);

  entry.set_text(to_string(32));
  TargetReshbox.pack_start(entry, PACK_SHRINK);

  Ascify_button.set_name("button");
  Ascify_button.set_label("Ascify");
  Ascify_button.set_sensitive(false);
  Ascify_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::on_ascify_button_clicked));

  button.set_label("Choose Image");
  button.signal_clicked().connect(
      sigc::mem_fun(*this, &MainWindow::on_button_clicked));

  TargetReshbox.pack_start(button, PACK_EXPAND_WIDGET);

  vbox.pack_start(Ascify_button, PACK_SHRINK);

  resultImage.set_name("canvas");
  resultImage.set_selectable(true);
  vbox.pack_start(resultImage, PACK_SHRINK);

  copy_button.set_name("button");
  copy_button.set_label("Copy");
  copy_button.signal_clicked().connect(
      [this]() { on_copy_button_clicked(resultImage); });
  vbox.pack_start(copy_button, PACK_SHRINK);
}

MainWindow::~MainWindow(){

};

void MainWindow::on_ADD_Char() {
  int index = IndexLabel_list.size();

  Label *index_label = manage(new Label(to_string(index + 1)));
  index_label->set_name("IDXL");

  Entry *ChartoDraw = manage(new Entry());
  ChartoDraw->set_name("CTD");
  // ChartoDraw->set_size_request(20, 20);
  //
  //  Set maximum width for the entry widget
  ChartoDraw->set_width_chars(1);

  // Set input mask to allow only one character
  // ChartoDraw->set_input_mask("X");

  Button *remove_button = manage(new Button("-"));
  remove_button->set_name("chb");
  //  remove_button->signal_clicked().connect(sigc::bind<Entry *>(
  //      sigc::mem_fun(*this, &MainWindow::on_DELETE_Char), index));
  //  remove_button->signal_clicked().connect(
  //      sigc::bind(sigc::mem_fun(*this, &MainWindow::on_DELETE_Char), index));

  remove_button->signal_clicked().connect(sigc::bind<Entry *>(
      sigc::mem_fun(*this, &MainWindow::on_DELETE_Char), ChartoDraw));

  IndexLabel_list.push_back(index_label);
  ChartoDraw_list.push_back(ChartoDraw);
  Remove_list.push_back(remove_button);

  charsHbox.pack_start(*index_label, PACK_SHRINK);
  charsHbox.pack_start(*ChartoDraw, PACK_SHRINK);
  charsHbox.pack_start(*remove_button, PACK_SHRINK);

  show_all_children();
}

void MainWindow::on_DELETE_Char(Entry *entryToRemove) {
  auto it_entry =
      find(ChartoDraw_list.begin(), ChartoDraw_list.end(), entryToRemove);
  int index = distance(ChartoDraw_list.begin(), it_entry);

  if (index < IndexLabel_list.size()) {
    for (int i = index; i < IndexLabel_list.size(); i++) {
      IndexLabel_list[i]->set_label(to_string(i));
    }

    charsHbox.remove(*IndexLabel_list[index]);
    charsHbox.remove(*ChartoDraw_list[index]);
    charsHbox.remove(*Remove_list[index]);

    // delete IndexLabel_list[index];
    IndexLabel_list.erase(IndexLabel_list.begin() + index);

    // delete ChartoDraw_list[index];
    ChartoDraw_list.erase(ChartoDraw_list.begin() + index);

    // delete Remove_list[index];
    Remove_list.erase(Remove_list.begin() + index);
  }
}

void MainWindow::on_Def() {
  int currentshadenum = IndexLabel_list.size();
  if (currentshadenum < shadeNum) {
    for (int i = currentshadenum; i < shadeNum; i++) {
      on_ADD_Char();
    }
  } else if (currentshadenum > shadeNum) {
    for (int i = currentshadenum; i > shadeNum - 1; i--) {
      on_DELETE_Char(ChartoDraw_list[i]);
    }
  }
  for (int i = 0; i < shadeNum; i++) {
    ChartoDraw_list[i]->set_text(shade[i]);
  }
}

void MainWindow::on_copy_button_clicked(Gtk::Label &label) {
  auto clipboard = Gtk::Clipboard::get();
  clipboard->set_text(label.get_text());
}

void MainWindow::on_button_clicked() {
  if (!entry.get_text().empty()) {

    // Create a FileChooserDialog

    Gtk::FileChooserDialog dialog("Please choose an image file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Asciify", Gtk::RESPONSE_OK);

    // Add filters to select only image files
    auto filter_image = Gtk::FileFilter::create();
    filter_image->set_name("Image files");
    filter_image->add_pixbuf_formats();
    dialog.add_filter(filter_image);

    // Show the FileChooserDialog and wait for user response
    int result = dialog.run();
    if (result != Gtk::RESPONSE_OK) {
      std::cerr << "Error: No file selected." << std::endl;
      return;
    }

    Ascify_button.set_sensitive(true);
    // Get the selected file path
    filename = dialog.get_filename();

    Ascify(filename);
  }
}

void MainWindow::on_ascify_button_clicked() {
  if (!entry.get_text().empty()) {
    if (filename != "") {
      Ascify(filename);
    } else {
      on_button_clicked();
    }
  }
}

void MainWindow::Ascify(string filename) {

  // Load the selected image
  Mat image = imread(filename);
  if (!image.data) {
    std::cerr << "Error: Unable to load image." << std::endl;
    return;
  }

  // Determine the aspect ratio of the image
  double aspectRatio =
      static_cast<double>(image.cols) / static_cast<double>(image.rows);

  int targetWidth;
  int targetHeight;

  if (aspectRatio < 1) {
    // Get the target height from the entry
    targetHeight = std::stoi(entry.get_text());
    // Calculate the target width based on the aspect ratio
    targetWidth = static_cast<int>(targetHeight * aspectRatio);
  } else if (aspectRatio > 1) {
    // Get the target width from the entry
    targetWidth = std::stoi(entry.get_text());
    // Calculate the target height based on the aspect ratio
    targetHeight = static_cast<int>(targetWidth / aspectRatio);
  } else {
    // Get the target width from the entry
    targetWidth = std::stoi(entry.get_text());
    // Calculate the target height based on the aspect ratio
    targetHeight = targetWidth;
  }

  // Resize the image while maintaining the aspect ratio
  Mat resized;
  cv::resize(image, resized, Size(targetWidth, targetHeight));

  int shadeNumR = IndexLabel_list.size();
  std::vector<string> shadeR;
  for (int i = 0; i < shadeNumR; i++) {
    shadeR.push_back(ChartoDraw_list[i]->get_text().substr(0, 1) +
                     ChartoDraw_list[i]->get_text().substr(0, 1));
  }

  int brightnessMap[resized.rows][resized.cols];
  std::stringstream resStream;
  res = "";
  // Iterate over pixels and calculate brightness
  for (int y = 0; y < resized.rows; ++y) {
    for (int x = 0; x < resized.cols; ++x) {
      Vec3b color = resized.at<Vec3b>(y, x);

      // Convert RGB to grayscale
      int grayscale = (color[0] + color[1] + color[2]) / 3;

      // Normalize to range [0, 255]
      grayscale = std::max(0, std::min(255, grayscale));

      // Map grayscale to range [0, 4]
      // int brightness = grayscale / 64;
      int brightness = grayscale / (256 / (shadeNumR - 1));

      // Assign the brightness value to the map
      brightnessMap[y][x] = brightness;

      resStream << shadeR[brightness];
    }
    resStream << "\n";
  }

  res = resStream.str();

  resultImage.set_text(res);

  resize(targetHeight * 10, targetWidth * 10);
}

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_path("style.css"); // Load CSS file

  auto screen = Gdk::Screen::get_default();
  auto style_context = Gtk::StyleContext::create();
  style_context->add_provider_for_screen(
      screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  MainWindow window; // Instantiate your MainWindow class
  window.show_all();

  return app->run(window);
}
