return {
  version = "1.2",
  luaversion = "5.1",
  tiledversion = "1.2.5",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 16,
  height = 9,
  tilewidth = 16,
  tileheight = 16,
  nextlayerid = 3,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "tileset",
      firstgid = 1,
      filename = "../../imgs/tileset.tsx",
      tilewidth = 16,
      tileheight = 16,
      spacing = 0,
      margin = 0,
      columns = 8,
      image = "../../imgs/tileset.png",
      imagewidth = 128,
      imageheight = 176,
      tileoffset = {
        x = 0,
        y = 0
      },
      grid = {
        orientation = "orthogonal",
        width = 16,
        height = 16
      },
      properties = {},
      terrains = {},
      tilecount = 88,
      tiles = {}
    }
  },
  layers = {
    {
      type = "tilelayer",
      id = 1,
      name = "Tile Layer 1",
      x = 0,
      y = 0,
      width = 16,
      height = 9,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 8, 8, 1, 8, 8, 8, 1, 1, 1, 1,
        1, 1, 11, 1, 1, 8, 1, 1, 1, 1, 1, 8, 1, 8, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 8, 11, 3, 2, 5, 5, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 8, 1, 1, 3, 1, 1, 1, 8, 1, 1, 8, 1,
        1, 1, 1, 1, 11, 1, 1, 8, 4, 3, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
      }
    },
    {
      type = "tilelayer",
      id = 2,
      name = "Tile Layer 2",
      x = 0,
      y = 0,
      width = 16,
      height = 9,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        81, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 83
      }
    }
  }
}
