
#ifndef DRAW_HPP
#define DRAW_HPP

#include "../epidemic/epidemic.hpp"
#include "curve/curve.hpp"
#include "grid/grid.hpp"
#include "key/key.hpp"
#include "text/text.hpp"

namespace pf {

class Draw {
 private:
  sf::RenderWindow& window_;

  Epidemic epidemic_;

  pf::Text text_;
  pf::Grid grid_;
  pf::Curve curve_;
  pf::Key key_;

 public:
  Draw(Epidemic const&);

  void draw_graph();
};
}  // namespace pf
#endif
