from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from PIL import Image

from cv2 import *
from numpy import fromstring, int8

window = 0
height = 500
width = 500
cubeWidth = width / 2
right = cubeWidth / 2
left = -right
far = cubeWidth / 2
near = -far
bottom = -cubeWidth / 2
top = -bottom

angles = [60, 75, 100]
perspCoef = [-0.46, 0.4, 1.32]
ORTHO = 0
PERSP0 = 1
PERSP1 = 2
PERSP2 = 3

def drawCube():
    # Left side
    glColor(1.0, 0.0, 0.0)
    glBegin(GL_QUADS)
    glVertex(left, bottom, far)
    glVertex(left, top, far)
    glVertex(left, top, near)
    glVertex(left, bottom, near)
    glEnd()

    # Right side
    glColor(0.0, 1.0, 0.0)
    glBegin(GL_QUADS)
    glVertex(right, far, bottom)
    glVertex(right, far, top)
    glVertex(right, near, top)
    glVertex(right, near, bottom)
    glEnd()

    # Bottom side
    glColor(1.0, 1.0, 0.0)
    glBegin(GL_QUADS)
    glVertex(right, far, bottom)
    glVertex(right, near, bottom)
    glVertex(left, near, bottom)
    glVertex(left, far, bottom)
    glEnd()

    # Top side
    glColor(1.0, 0.0, 1.0)
    glBegin(GL_QUADS)
    glVertex(right, far, top)
    glVertex(right, near, top)
    glVertex(left, near, top)
    glVertex(left, far, top)
    glEnd()

    # Far side
    glColor(0.0, 0.0, 1.0)
    glBegin(GL_QUADS)
    glVertex(right, far, bottom)
    glVertex(left, far, bottom)
    glVertex(left, far, top)
    glVertex(right, far, top)
    glEnd()

def drawOrtho():
    glMatrixMode(GL_PROJECTION)
    indent = cubeWidth / 2
    glOrtho(left - indent, right + indent, bottom - indent, top + indent, near / 2, far * 2)

def drawPerspective(angle):
    glMatrixMode(GL_PROJECTION)
    aspect = width / height
    gluPerspective(angle, aspect, far / 2, far * 10)

    eye = [(right + left) / 2, (near + far) / 2 - cubeWidth * 2, (bottom + top) / 2]
    center = [0, (near + far) / 2, 0]
    up = [0, 0, 1]

    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2])

def catch():
    '''
    global state
    screenshot = glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE)
    img = Image.frombytes("RGB", (width, height), fromstring(screenshot, int8))
    img.save("out" + str(state) + ".bmp")#, "BMP")
#    snapshot = imdecode(img.tobitmap(), CV_LOAD_IMAGE_COLOR)
#    imwrite("out.bmp", snapshot)
'''
    pass

def draw():
    global read
    global state
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    glViewport(0, 0, width, height)

    if state == ORTHO:
        drawOrtho()
    else:
        drawPerspective(angles[state - 1])
        glTranslatef(0, perspCoef[state - 1] * near, 0)

    if not read[state]:
        catch()
        read[state] = True


    drawCube()

    glutSwapBuffers()

def keyboardFun(key, x, y):
    global state
    state = (state + 1) % (PERSP2 + 1)
    if key == '\033':
        exit()

state = ORTHO
read = [False, False, False, False]

glutInit()
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA)
glutInitWindowSize(width, height)
glutCreateWindow("Cube")

glutDisplayFunc(draw)
glutIdleFunc(draw)
glutKeyboardFunc(keyboardFun)

glutMainLoop()

