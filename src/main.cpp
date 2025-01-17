#include <gtk/gtk.h>
#include <pango/pangocairo.h>
#include <math.h>
#include <cmath>

//export DISPLAY=:0
//xset -dpms ; xset s off
//gcc $(pkg-config --cflags gtk+-3.0) -o hello-world-gtk main.cpp $(pkg-config --libs gtk+-3.0) -lrt -lm -lpthread

// static void activate (GtkApplication *app, gpointer user_data)
// {
//   GtkWidget *window;
//   GtkWidget *button;

//   window = gtk_application_window_new (app);
//   gtk_window_set_title (GTK_WINDOW (window), "Hello");
//   gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

//   button = gtk_button_new_with_label ("Hello World");
//   g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
//   gtk_window_set_child (GTK_WINDOW (window), button);

//   gtk_window_present (GTK_WINDOW (window));
// }

// def draw_radial_gradient_rect(self, ctx)
// {
//         x0, y0 = 0.3, 0.3
//         x1, y1 = 0.5, 0.5
//         r0 = 0
//         r1 = 1        
//         pattern = cairo.RadialGradient(x0, y0, r0, x1, y1, r1) 
//         pattern.add_color_stop_rgba(0, 1,1,0.5, 1)   
//         pattern.add_color_stop_rgba(1, 0.2,0.4,0.1, 1)   
//         ctx.rectangle(0, 0, 1, 1)       
//         ctx.set_source(pattern)
//         ctx.fill()
// }

class NaviBall
{
  private:
  double displayWidth = 720.0;
  double displayHeight = 720.0;
  double offset = displayWidth * 0.01388888;
  double halfWidth = (displayWidth / 2.0);
  double outerBand0 = (halfWidth - offset) * (1335.0 / 1335.0);
  double outerBand1 = (halfWidth - offset) * (1285.0 / 1335.0);
  double outerBand2 = (halfWidth - offset) * (1265.0 / 1335.0);

  double innerBand0 = (halfWidth - offset) * 0.70;
  double innerBand1 = innerBand0 * 0.95;
  double innerBand2 = innerBand1 * 0.95;

  double oneRadian = M_PI / 180.0;
  double centerX = halfWidth;
  double centerY = halfWidth;

  public:

  GtkWidget *widget = NULL;
  cairo_t *cr = NULL;
  gpointer data;

  double heading_sat = 0.0;
  double heading_mag = 0.0;
  double aparentWindAngle = 359.9;
  double aparentWindSpeed = 0.0;
  double depth_port = 0.0;
  double depth_starboard = 0.0;

/***************************************************************************************************/
  void drawHeadingText() {
    cairo_set_font_size (cr, 30.0);
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL /*CAIRO_FONT_WEIGHT_BOLD*/);

    cairo_translate(cr, centerX, centerY);

    const double offsetFromBand = outerBand2 - 20;
    cairo_rotate(cr, (0.0 + heading_sat) * G_PI / 180.0);
    drawText("N",   0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("30",  0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("60",  0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("E",   0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("120", 0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("150", 0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("S",   0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("210", 0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("240", 0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("W",   0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("300",  0, -offsetFromBand, 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("330",  0, -offsetFromBand, 0.0);

    cairo_identity_matrix(cr); //Reset the CTM
    cairo_move_to(cr, centerX, centerY);
    cairo_stroke(cr);
  }

/***************************************************************************************************/
  void drawAWAText() {
    cairo_set_font_size (cr, 20.0);
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL /*CAIRO_FONT_WEIGHT_BOLD*/);

    cairo_translate(cr, centerX, centerY);

    const double offsetFromBand = 12.0;
    drawText("0",   0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("30",  0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("60",  0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("90",  0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("120", 0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("150", 0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("180", 0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("150", 0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("120", 0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("90",  0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("60",  0, -(innerBand0 + offsetFromBand), 0.0);
    cairo_rotate(cr, 30.0 * G_PI / 180.0);
    drawText("30",  0, -(innerBand0 + offsetFromBand), 0.0);

    cairo_identity_matrix(cr); //Reset the CTM
    cairo_move_to(cr, centerX, centerY);
    cairo_stroke(cr);
  }

/***************************************************************************************************/
  void drawText(const char* text, double x, double y, double angle) {
    cairo_font_extents_t fe;
	  cairo_text_extents_t te;
    double xAdj;
    double yAdj;
    
    //Adjust for size of the Text.
    cairo_font_extents (cr, &fe);
    cairo_text_extents (cr, text, &te);
    xAdj = x - te.x_bearing - (te.width / 2);
    yAdj = y - fe.descent + (fe.height / 2);

    //Fill first then draw an outline to make the text crisp
    cairo_move_to(cr, xAdj, yAdj);
    cairo_text_path(cr, text);
    cairo_set_source_rgb(cr, 101.0/255.0, 171.0/255.0, 156.0/255.0);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 49.0/255.0, 96.0/255.0, 91.0/255.0);
    cairo_set_line_width(cr, 0.5);
    cairo_stroke(cr);
  }

/***************************************************************************************************/
  void drawRadiaLines() {
    //double radius = (halfWidth - offset);

    //Draw outer Band Gradient
    double rad = outerBand2;
    double rad2 = innerBand0 + 10;
    cairo_pattern_t* radialGradient = cairo_pattern_create_radial(centerX, centerY, rad, centerX, centerY, rad2);
    cairo_pattern_add_color_stop_rgb(radialGradient, 0.0, 0.04, 0.30, 0.30);
    cairo_pattern_add_color_stop_rgb(radialGradient, 1.0, 0.0, 0.06, 0.06);
    cairo_set_source(cr, radialGradient);
    cairo_arc(cr, centerX, centerY, rad, 0.0, 2.0 * G_PI);
    cairo_fill(cr);

    //Draw outer Circle of hash marks.
    // set color
    cairo_set_source_rgb(cr, 0.0, 0.5, 0.5);
    // set the line width
    cairo_set_line_width(cr, 1);

    //Rotate in a circle dawing the minor hash marks
    for( int deg = 0; deg < 360; deg += 1)
    {
      double X = cos( (deg + heading_sat) * oneRadian );
      double Y = sin( (deg + heading_sat) * oneRadian );
      cairo_move_to(cr, X * outerBand1 + centerX, Y * outerBand1 + centerY);
      cairo_line_to(cr, X * outerBand0 + centerX, Y * outerBand0 + centerY);

      X = cos( deg * oneRadian );
      Y = sin( deg * oneRadian );
      cairo_move_to(cr, X * innerBand1 + centerX, Y * innerBand1 + centerY);
      cairo_line_to(cr, X * innerBand0 + centerX, Y * innerBand0 + centerY);
    }
    cairo_stroke(cr);

    //Draw inner Circle of hash marks.
    // set color
    cairo_set_source_rgb(cr, 0.0, 0.5, 0.5);
    // set the line width
    cairo_set_line_width(cr, 2);

    //Rotate in a circle dawing the semi-major hash marks
    for( int deg = 0; deg < 360; deg += 5)
    {
      double X = cos( (deg + heading_sat) * oneRadian );
      double Y = sin( (deg + heading_sat) * oneRadian );
      cairo_move_to(cr, X * outerBand1 + centerX, Y * outerBand1 + centerY);
      cairo_line_to(cr, X * outerBand0 + centerX, Y * outerBand0 + centerY);

      X = cos( deg * oneRadian );
      Y = sin( deg * oneRadian );
      cairo_move_to(cr, X * innerBand1 + centerX, Y * innerBand1 + centerY);
      cairo_line_to(cr, X * innerBand0 + centerX, Y * innerBand0 + centerY);
    }
    cairo_stroke(cr);

    /* set color for rectangle */
    cairo_set_source_rgb(cr, 0.0, 0.5, 0.5);
    /* set the line width */
    cairo_set_line_width(cr, 2);

    //Rotate in a circle dawing the major hash marks
    for( int deg = 0; deg < 360; deg += 10)
    {
      double X = cos( (deg + heading_sat) * oneRadian );
      double Y = sin( (deg + heading_sat) * oneRadian );
      cairo_move_to(cr, X * outerBand2 + centerX, Y * outerBand2 + centerY);
      cairo_line_to(cr, X * outerBand0 + centerX, Y * outerBand0 + centerY);

      X = cos( deg * oneRadian );
      Y = sin( deg * oneRadian );
      cairo_move_to(cr, X * innerBand2 + centerX, Y * innerBand2 + centerY);
      cairo_line_to(cr, X * innerBand0 + centerX, Y * innerBand0 + centerY);
    }
    cairo_stroke(cr);

    //Draw Water Gradient
    rad = innerBand2 - 15;
    cairo_pattern_t* linearGradient = cairo_pattern_create_linear(centerX, centerY, centerX, centerY + rad);
    cairo_pattern_add_color_stop_rgb(linearGradient, 0.0, 0.05, 0.5, 0.9);
    cairo_pattern_add_color_stop_rgb(linearGradient, 1.0, 0.0, 0.0, 0.1);
    cairo_set_source(cr, linearGradient);
    cairo_arc(cr, centerX, centerY, rad, 0.0, G_PI);
    cairo_fill(cr);

    //Draw Horizon Line.
    cairo_set_source_rgb(cr, 0.0, 0.75, 0.75);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, centerX - (rad + 7), centerY);
    cairo_line_to(cr, centerX + (rad + 7), centerY);
    cairo_stroke(cr);
  }

  /***************************************************************************************************/
  void drawWindText() {
    cairo_set_font_size (cr, 20.0);
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL /*CAIRO_FONT_WEIGHT_BOLD*/);

    cairo_translate(cr, centerX, centerY);

    drawText("18.3", 0, -50, 0.0);
    
  }

  /***************************************************************************************************/
  void drawAWAIndicator() {
    double width = 26;
    double height = 50;
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_set_line_width(cr, 2);

    cairo_translate(cr, centerX, centerY); // translate origin back
    cairo_rotate(cr, aparentWindAngle * G_PI / 180.0); // Convert angle to radians

    cairo_move_to(cr, 0, -innerBand0);
    cairo_line_to(cr, width / 2.0, -innerBand0 - height);
    cairo_line_to(cr, -width / 2.0, -innerBand0 - height);
    cairo_close_path(cr);
    cairo_set_source_rgb(cr, 101.0/255.0, 171.0/255.0, 156.0/255.0);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);

    cairo_identity_matrix(cr); //Reset the CTM
  }

/***************************************************************************************************/
  PangoFontDescription* createFontDescription(const char* familyName, const char* faceName) {
    
    PangoFontFamily ** families;
    int n_families;
    PangoFontFamily * family = NULL;
    PangoFontMap* fontmap = pango_cairo_font_map_get_default();
    pango_font_map_list_families (fontmap, &families, &n_families);
    for(int q = 0; q < n_families; q++)
    {
      family = families[q];
      const char * family_name = pango_font_family_get_name (family);
      if(strcmp(familyName, family_name) == 0)
      {
        PangoFontFace** faces;
        int n_faces = 0;
        pango_font_family_list_faces (family, &faces, &n_faces);
        for (int w = 0; w < n_faces; w++) 
        {
          PangoFontFace* face = faces[w];
          const char * face_name = pango_font_face_get_face_name(face);
          if(strcmp(faceName, face_name) == 0)
          {
            return pango_font_face_describe(face);
          }
        }
      }
    }

    return NULL;
  }

  /* Simple example to use pangocairo to render rotated text */
  /***************************************************************************************************/
  void draw_text () {
    #define FONT_WITH_MANUAL_SIZE "Times new roman,Sans"
    #define FONT_SIZE 16
    #define DEVICE_DPI 175

    /* The following number applies a cairo CTM.  Tests for
    * https://bugzilla.gnome.org/show_bug.cgi?id=700592
    */
    #define TWEAKABLE_SCALE ((double) 1.0)

    PangoLayout *layout;

    /* Center coordinates on the middle of the region we are drawing
    */
    cairo_translate (cr, centerX, centerY);

    /* Create a PangoLayout, set the font and text */
    layout = pango_cairo_create_layout (cr);

    pango_layout_set_text (layout, "25.8°", -1);

    GError** error = NULL;
    PangoAttrList* attr_list = NULL;
    gunichar* accel_char = NULL;
    char* resultTest = NULL;

    double AWA = 25.8;
    double AWS = 8.2;
    double Depth = 186.2;
    double STW = AWS / 2.0;

    uint32_t AWA_IntegerPart = uint32_t(AWA);
    // uint32_t AWA_fractionalPart = uint32_t((AWA - double(AWA_IntegerPart)) * 10.0);

    char markup_text[256];
    int width, height;
    double textY = -230;

    PangoFontDescription* fontDescription = createFontDescription("Genos", "Medium");
    pango_font_description_set_absolute_size(fontDescription, FONT_SIZE * DEVICE_DPI * PANGO_SCALE / (72.0 * TWEAKABLE_SCALE));
    pango_layout_set_font_description(layout, fontDescription);

    /*************************************************************/
    snprintf(markup_text, 256, "<span foreground=\"white\" size=\"x-large\">%u</span><span foreground=\"white\" size=\"medium\">°</span>", AWA_IntegerPart);
    
    if( FALSE == pango_parse_markup(markup_text, -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    if( FALSE == pango_parse_markup("<span foreground=\"white\" size=\"x-small\">AWA</span>", -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 50);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    uint32_t AWS_IntegerPart = uint32_t(AWS);
    uint32_t AWS_fractionalPart = uint32_t((AWS - double(AWS_IntegerPart)) * 10.0);
    snprintf(markup_text, 256, "<span foreground=\"white\" size=\"x-large\">%u.</span><span foreground=\"white\" size=\"medium\">%u</span><span foreground=\"white\" size=\"xx-small\"> kt</span>", AWS_IntegerPart, AWS_fractionalPart);
    if( FALSE == pango_parse_markup(markup_text, -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 80);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    if( FALSE == pango_parse_markup("<span foreground=\"white\" size=\"x-small\">AWS</span>", -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 80 + 50);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    uint32_t Depth_IntegerPart = uint32_t(Depth);
    uint32_t Depth_fractionalPart = uint32_t((Depth - double(Depth_IntegerPart)) * 10.0);
    snprintf(markup_text, 256, "<span foreground=\"white\" size=\"x-large\">%u.</span><span foreground=\"white\" size=\"medium\">%u</span><span foreground=\"white\" size=\"xx-small\"> ft</span>", Depth_IntegerPart, Depth_fractionalPart);
    if( FALSE == pango_parse_markup(markup_text, -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 275);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    if( FALSE == pango_parse_markup("<span foreground=\"white\" size=\"x-small\">Depth</span>", -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 275 + 50);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    uint32_t STW_IntegerPart = uint32_t(STW);
    uint32_t STW_fractionalPart = uint32_t((STW - double(STW_IntegerPart)) * 10.0);
    snprintf(markup_text, 256, "<span foreground=\"white\" size=\"x-large\">%u.</span><span foreground=\"white\" size=\"medium\">%u</span><span foreground=\"white\" size=\"xx-small\"> kt</span>", STW_IntegerPart, STW_fractionalPart);
    if( FALSE == pango_parse_markup(markup_text, -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 350);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    if( FALSE == pango_parse_markup("<span foreground=\"white\" size=\"x-small\">STW</span>", -1, 0, &attr_list, &resultTest, accel_char, error))
    {
      printf("pango_parse_markup has an error.\n");
    }

    pango_layout_set_attributes(layout, attr_list);
    pango_layout_set_text(layout, resultTest, -1);

    cairo_save(cr);
    /* Inform Pango to re-layout the text with the new transformation */
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_size(layout, &width, &height);
    cairo_move_to(cr,( - (((double)width) / PANGO_SCALE) / 2.0) , textY + 350 + 50);
    pango_cairo_show_layout(cr, layout);
    cairo_restore(cr);

    /*************************************************************/
    pango_font_description_free(fontDescription);

    /* free the layout object */
    g_object_unref (layout);
  }

  void Draw() {
    /* Set color for background */
    cairo_set_source_rgb(cr, 0, 0, 0);
    /* fill in the background color*/
    cairo_paint(cr);

    drawRadiaLines();
    drawAWAText();
    drawHeadingText();
    drawAWAIndicator();
    draw_text();
  }
};

NaviBall naviBall;

/***************************************************************************************************/
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {

  if(naviBall.widget == NULL)
  {
    naviBall.widget = widget;
    naviBall.cr = cr;
    naviBall.data = data;
  }

  naviBall.Draw();

  return FALSE;
}

/***************************************************************************************************/
gboolean key_callback ( GtkWidget *widget, GdkEventKey *event ) {
    ( void ) widget;
    if ( event->state & GDK_CONTROL_MASK )
    {
        if ( event->keyval == GDK_KEY_c || event->keyval == GDK_KEY_C )
        {
            g_print ( "CTRL + C was catched\n" );
						gtk_main_quit();
        }

        return FALSE;
    }

    return TRUE;
}

/***************************************************************************************************/
gboolean timer_exe(GtkWidget * window)
{
  if(naviBall.heading_sat < 0.0)
  {
    naviBall.heading_sat = 360.0;
  }
  else if(naviBall.heading_sat >= 360.0)
  {
    naviBall.heading_sat = 0.0;
  }
  naviBall.heading_sat += 0.2;

  if(naviBall.aparentWindAngle < 0.0)
  {
    naviBall.aparentWindAngle = 360.0;
  }
  else if(naviBall.aparentWindAngle >= 360.0)
  {
    naviBall.aparentWindAngle = 0.0;
  }
  naviBall.aparentWindAngle -= 0.2;

  //tell our window it is time to draw our animation.
  gtk_widget_queue_draw_area(window, 0, 0, 720, 720);

  return TRUE;
}

/***************************************************************************************************/
static void list_fonts() {
    PangoFontFamily ** families;
    int n_families;

    PangoFontMap* fontmap = pango_cairo_font_map_get_default();
    pango_font_map_list_families (fontmap, & families, &n_families);
    printf ("There are %d families\n", n_families);
    for (int i = 0; i < n_families; i++) 
    {
      PangoFontFamily * family = families[i];
      const char * family_name;

      family_name = pango_font_family_get_name (family);
      printf ("Family %d: %s\n", i, family_name);

      PangoFontFace** faces;
      int n_faces = 0;

      pango_font_family_list_faces (family, &faces, &n_faces);
      printf ("  There are %d faces\n", n_faces);
      for (int j = 0; j < n_faces; j++) 
      {
        PangoFontFace* face = faces[j];
        const char * face_name = pango_font_face_get_face_name (face);
        printf ("  Face %d: %s\n", j, face_name);
      }

      // pango_font_describe()
      // pango_font_describe_with_absolute_size()
      // pango_font_face_describe()
      //PangoFontDescription* pango_font_face_describe(PangoFontFace* face);

      // void pango_cairo_font_map_set_resolution (PangoCairoFontMap* fontmap,double dpi)
    }
    g_free (families);
}

/***************************************************************************************************/
int main (int argc, char **argv)
{
  // GtkApplication *app;
  // int status;

  // app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  // g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  // status = g_application_run (G_APPLICATION (app), argc, argv);
  // g_object_unref (app);

  // return status;

  //---------------------------------
	//----- CREATE THE GTK WINDOW -----
	//---------------------------------
	GtkWidget *MainWindow;
	GtkWidget *da;

	gtk_init(&argc, &argv);

	GdkRectangle workarea = {0, 0, 0 ,0};
	gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea);
  printf ("W: %u x H:%u\n", workarea.width, workarea.height);
	
  GdkCursor* cursor = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_BLANK_CURSOR);

  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); 		//GTK_WINDOW_TOPLEVEL = Has a titlebar and border, managed by the window manager. 
	gtk_window_set_title(GTK_WINDOW(MainWindow), "NavUI");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 720, 720);		//Size of the the client area (excluding the additional areas provided by the window manager)
	gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
	
	//Close the application if the x button is pressed if ALT+F4 is used
	g_signal_connect(G_OBJECT(MainWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT(MainWindow), "key_press_event", G_CALLBACK(key_callback), NULL);

	da = gtk_drawing_area_new();
	gtk_widget_set_size_request (da, 720, 720);
	g_signal_connect (da, "draw", G_CALLBACK(draw_cb),  NULL);

	gtk_container_add (GTK_CONTAINER (MainWindow), da);
	//gtk_widget_show(da);
	//gtk_widget_show (window);

	gtk_widget_show_all(MainWindow);
	gtk_window_fullscreen(GTK_WINDOW(MainWindow));

  GdkWindow* gdkWindow = gtk_widget_get_window(da);
  gdk_window_set_cursor(gdkWindow, cursor);

  g_timeout_add(33, (GSourceFunc)timer_exe, MainWindow);

	//----- ENTER THE GTK MAIN LOOP -----
	gtk_main();		//Enter the GTK+ main loop until the application closes.

	return 0;
}
