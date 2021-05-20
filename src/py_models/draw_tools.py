from PIL import Image, ImageDraw, ImageFont
import numpy as np

# Adds a square red point (denominated by p) to the given drawing.
def draw_point(drawing, p, r=2.5):
  box = [p[0]-r, p[1]-r, p[0]+r, p[1]+r]
  drawing.ellipse(xy=box, fill='red', outline='red')


# Draws line segments (given by segments) and square points at the endpoints.
# This is code recycled from my old implementations. It anecdotally works.
#
# If one wishes to have labels, just provide a Pointset
def draw_line_segments(segments, img_w=300, img_h=300, margin=50, pointset=None):
    minX = 10
    minY = 10

    all_x_c = [x[0][0] for x in segments]
    all_x_c.extend([x[1][0] for x in segments])
    all_x_c = np.array(all_x_c)
    
    all_y_c = [x[0][1] for x in segments]
    all_y_c.extend([x[1][1] for x in segments])
    all_y_c = np.array(all_y_c)
    
    span = np.max(segments) - np.min(segments)
    ratio = (max(img_w, img_h)-margin)/span
    shiftX = -np.min(all_x_c)
    shiftY = -np.min(all_y_c)
    
    qx = lambda v : (v + shiftX) * ratio + minX
    qy = lambda v : (v + shiftY) * ratio + minY
    
    img = Image.new('RGB', (img_w, img_h), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    
    for segment in segments:
        draw.line((qx(segment[0][0]), qy(segment[0][1]), qx(segment[1][0]), qy(segment[1][1])), fill=256)
    for segment in segments:
        draw_point(draw, [qx(segment[0][0]), qy(segment[0][1])])
        draw_point(draw, [qx(segment[1][0]), qy(segment[1][1])])
    
    if pointset is not None:
      # kinda hacky way to get a font -- works on Mac only
      font = ImageFont.truetype('/System/Library/Fonts/Monaco.dfont', size=20)
      for i, p in enumerate(pointset.points):
        draw.text((qx(p[0]), qy(p[1])), str(i), (0, 0, 0), font=font)

    return img


# Receives an EuclideanSpanner object and draws it. Unfortunately, this
# implementations is currently missing labels on points.

def draw_euclidean_spanner(spanner, img_w=300, img_h=300, margin=50):
  labels = spanner.labels()

  segments = []
  for i in range(len(labels)):
    for j in range(i+1, len(labels)):
      if spanner.query_edge(labels[i], labels[j]) == True:
        segments.append([spanner.coordinate(labels[i]),
                         spanner.coordinate(labels[j])])

  return draw_line_segments(segments, img_w, img_h, margin)


# Extract the line segments contained in a file.
def get_segments_from_file(file_path):
  file = open(file_path, 'r')
  lines = file.readlines()
  
  n = int(lines[0])
  print('N =', n)
  print(lines[1] + lines[2] + lines[3])
  
  parseLine = lambda ln : [[float(ln.split()[0]), float(ln.split()[1])],\
                            [float(ln.split()[2]), float(ln.split()[3])]]
  segments = [parseLine(ln) for ln in lines[4:]]
  
  return segments