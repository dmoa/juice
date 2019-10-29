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
  nextlayerid = 5,
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
      name = "ground",
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
        1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 5, 1, 1, 1, 6, 1, 1, 1, 1, 6, 1,
        1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
      }
    },
    {
      type = "tilelayer",
      id = 2,
      name = "blocks",
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
        65, 66, 66, 66, 66, 66, 66, 0, 0, 66, 66, 66, 66, 66, 66, 67,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 24, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 32, 0, 0, 0, 88,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        73, 0, 0, 0, 0, 62, 63, 64, 0, 50, 0, 0, 0, 0, 0, 72,
        73, 49, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        73, 57, 58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        81, 82, 82, 82, 82, 82, 82, 0, 0, 0, 82, 82, 82, 82, 82, 83
      }
    },
    {
      type = "tilelayer",
      id = 4,
      name = "walk through",
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 38, 39, 40, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 46, 47, 48, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 54, 55, 56, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
