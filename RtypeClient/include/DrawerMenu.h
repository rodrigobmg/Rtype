#pragma once

#include <array>

#include "ADrawer.h"
#include "DrawableGeneric.h"
#include "FactoryDrawable.h"
#include "DrawerUDrawable.h"
#include "IInputManagerSFML.h"

#include <vector>

class DrawerMenu : public ADrawer // no inheritance from DrawerLayer because it doesnt upgrade its targets
{
 public:
  DrawerMenu(); // TODO: give skins for buttons/arrow ?

  virtual void drawTo(IGraphicsManager*) const override;
  virtual void drawTo(IGraphicsManager*, const ValueDrawer&) const override;

  virtual void update(float ms) override;

  void checkInput(IInputManagerSFML*);

  void addButton(); // TODO: give a string ?
  int getSelectedId() const; // -1 means no selection

  void selectionForward();
  void selectionBackward();
  void select();
  void validate();

  enum selectionType
  {
    UNSELECTED,
    HOVER,
    SELECTED,
    VALIDATED
  };
  selectionType getSelectionType() const;
 private:
  void updateArrowPosition();
  int selectionId;
  selectionType status;
  std::vector<DrawerUDrawable> buttons;
  DrawerUDrawable arrow;
};
