return {
  version = "1.2",
  luaversion = "5.1",
  tiledversion = "1.3.0",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 16,
  height = 8,
  tilewidth = 16,
  tileheight = 16,
  nextlayerid = 10,
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
      imageheight = 224,
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
      tilecount = 112,
      tiles = {}
    }
  },
  layers = {
    {
      type = "tilelayer",
      id = 6,
      name = "ground",
      x = 0,
      y = 0,
      width = 16,
      height = 8,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 5, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
      }
    },
    {
      type = "tilelayer",
      id = 7,
      name = "block layer 2 (use if only necessary)",
      x = 0,
      y = 0,
      width = 16,
      height = 8,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        0, 0, 0, 0, 0, 0, 0, 66, 66, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      type = "tilelayer",
      id = 8,
      name = "blocks",
      x = 0,
      y = 0,
      width = 16,
      height = 8,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        65, 66, 66, 66, 66, 66, 66, 15, 16, 66, 66, 66, 66, 66, 66, 67,
        73, 0, 0, 0, 0, 0, 0, 23, 24, 0, 0, 0, 0, 0, 0, 75,
        73, 0, 0, 0, 0, 0, 0, 31, 32, 49, 0, 0, 0, 0, 0, 75,
        86, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        78, 0, 0, 0, 0, 0, 0, 0, 58, 0, 0, 0, 0, 0, 0, 72,
        73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
        92, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 93
      }
    },
    {
      type = "tilelayer",
      id = 9,
      name = "walk through",
      x = 0,
      y = 0,
      width = 16,
      height = 8,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        0, 35, 36, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 43, 44, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 51, 52, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 59, 0, 61, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  }
}
