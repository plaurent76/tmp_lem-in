Skip to content
 
Search or jump to…

Pull requests
Issues
Marketplace
Explore
 @Edorenta Sign out
1
0 0 jnederlo/lemin_visualizer
 Code  Issues 0  Pull requests 0  Projects 0  Wiki  Insights
lemin_visualizer/lemin_visual/lemin_visual.pyde
6ecd6ef  on Oct 23, 2017
@jnederlo jnederlo finished visualizer
     
292 lines (258 sloc)  8.53 KB


scl = 20

w = 500
h = 500

# count = 0

def take_data(data, data_arr):
    # print "num_ants = ", num_ants
    z = 0
    j = 0
    turn = 1
    myiter = iter(range(1, len(data)))
    for i in myiter:
        if not data[i]:
            pass
        elif "#" in data[i][0]:
            # print data[i]
            # next(myiter, None)
            if "##start" in data[i]:
                i += 1
                data_arr[j] = room(data[i][0], int(data[i][1])*scl, int(data[i][2])*scl, int(z)*scl*2)
                data_arr[j].set_start()
                # print data_arr[j].name, data_arr[j].x, data_arr[j].y, data_arr[j].z, data_arr[j].is_start , data_arr[j].is_end 
                room.num_rooms += 1
                # i -= 1
                # continue
                j += 1
                next(myiter, None)
            elif "##end" in data[i]:
                i += 1
                # print data[i]
                data_arr[j] = room(data[i][0], int(data[i][1])*scl, int(data[i][2])*scl, int(z)*scl*2)
                data_arr[j].set_end()
                # print data_arr[j].name, data_arr[j].x, data_arr[j].y, data_arr[j].z, data_arr[j].s, data_arr[j].is_end 
                room.num_rooms += 1
                # i -= 1
                # continue
                next(myiter, None)
                j += 1
            else:
                pass
        elif "-" in str(data[i]) and "L" not in str(data[i]):
            link_room = data[i][0].split('-')
            for k in range(room.num_rooms):
                room_name = data_arr[k].get_name()
                if str(room_name) == link_room[0]:
                    for l in range(room.num_rooms):
                        link_name = data_arr[l].get_name()
                        if str(link_name) == link_room[1]:
                            data_arr[k].add_link(data_arr[l])
                            # print "room = ", data_arr[k].name, "link = ", data_arr[k].link
                            break
                    break
        elif "L" in str(data[i]):
            # print "data[i] = ", data[i]
            for j in range(len(data[i])):
                move_line = data[i][j].split('-')
                print move_line
                for m in range(room.num_rooms):
                    room_name = data_arr[m].get_name()
                    # print "room_name = ", room_name
                    # print "move_line[1] = ", move_line[1]
                    if room_name == move_line[1]:
                        data_arr[m].set_move(turn)
                        print "data_arr[m].move = ", data_arr[m].move
            turn += 1
                # print "move_line = ", move_line
            # print data[i]
            # pass
        else:
            data_arr[j] = room(data[i][0], int(data[i][1])*scl, int(data[i][2])*scl, int(z)*scl*2)
            # print data_arr[j].name, data_arr[j].x, data_arr[j].y, data_arr[j].z, data_arr[j].s, data_arr[j].e
            room.num_rooms += 1
            j += 1
        z += 1
        global turns
        turns = turn
    return (data_arr)



def draw_rooms():
    for i in range(room.num_rooms):
        if data_arr[i].is_start is True:
            pushMatrix()
            noStroke()
            fill(200, 100, 0) 
            lights()
            translate(data_arr[i].x, data_arr[i].y, data_arr[i].z+scl*2)
            box(scl)
            popMatrix()
        elif data_arr[i].is_end is True:
            pushMatrix()
            stroke(255)
            fill(0, 200, 200, env.value)
            lights()
            translate(data_arr[i].x, data_arr[i].y, data_arr[i].z+scl*2)
            box(scl)
            popMatrix()
        elif data_arr[i].is_start is False and data_arr[i].is_end is False:
            pushMatrix()
            lights()
            noStroke()
            fill(255)
            for k in range(len(data_arr[i].move)):
                print "data_arr[i].name = ", data_arr[i].name
                print "data_arr[i].move = ", data_arr[i].move[k]
                print "len = ", len(data_arr[i].move)
                # delay(5000)
                if env.count != data_arr[i].move[k]:
                    fill(255)
                    # print "data_arr[i].name = ", data_arr[i].name
                else:
                    fill(100)
                    break
            # print "turns = ", turns
            translate(data_arr[i].x, data_arr[i].y, data_arr[i].z+scl*2)
            sphere(scl/2)
            popMatrix()
        # print data_arr[i].name, data_arr[i].x, data_arr[i].y, data_arr[i].z, data_arr[i].s, data_arr[i].e, data_arr[i].link

def draw_lines():
    for j in range(room.num_rooms):
        if not data_arr[j].link:
            pass
        else:
            pushMatrix()
            stroke(5000)
            stroke(255)
            # print data_arr[j].x, data_arr[j].y, data_arr[j].z, data_arr[j].link[0].x, data_arr[j].link[0].y, data_arr[j].link[0].z
            for i in range(len(data_arr[j].link)):
                line(data_arr[j].x, data_arr[j].y, data_arr[j].z, data_arr[j].link[i].x, data_arr[j].link[i].y, data_arr[j].link[i].z)
            popMatrix()

def setup():
    frameRate(30)
    size(1000, 800, P3D)
    with open("bmap.txt") as f:
        data = [ lines.split() for lines in f ]
    print data
    print "env.num_ants = ", env.num_ants
    env.num_ants = data[0][0]
    print "env.num_ants = ", env.num_ants
    print "env/value = ", env.value
    env.value = 255 // int(env.num_ants)
    print "env/value = ", env.value
    global data_arr
    data_arr = [0 for x in range(len(data) -1)]
    data_arr = take_data(data, data_arr)

    # # def draw():
    # background(0)
    # change_view()
    # translate(100, 100)
    # rotate_map()
    # reset()
    # draw_rooms()
    # draw_lines()
  
def draw():
    background(0)
    change_view()
    translate(100, 100)
    rotate_map()
    reset()
    draw_rooms()
    draw_lines()

def mouseReleased():
    env.count += 1
    for i in range(room.num_rooms):
        if data_arr[i].is_end is True:
            for k in range(len(data_arr[i].move)):
                print "env.value = ", env.value
                if env.count == data_arr[i].move[k]:
                    env.value += (255 / (int(env.num_ants) + 1))
    if env.count == turns + 1:
        env.count = 0
        # env.value = 255 / int(env.num_ants)
        env.value = 0
    

    
def zoom():
    if keyPressed is True:
        if key == '-':
            env.eyeZ += 100
        if key == '+':
            env.eyeZ -= 100

def pan():
    if keyPressed is True:
        if key == 'a':
            env.centerX += 10
        if key == 'd':
            env.centerX -= 10
        if key == 'w':
            env.centerY += 10
        if key == 's':
            env.centerY -= 10

def change_view():
    camera(env.eyeX, env.eyeY, env.eyeZ, env.centerX, env.centerY, env.centerZ, env.upX, env.upY, env.upZ)
    zoom()
    pan()

def rotate_map():
    rotateX(env.x % 2*PI)
    rotateY(env.y % 2*PI)
    rotateZ(env.z % 2*PI)
    if keyPressed is True:
        if key == CODED:
            if keyCode == UP:
                env.x += PI/256
            if keyCode == DOWN:
                env.x -= PI/256
            if keyCode == LEFT:
                env.y -= PI/256
            if keyCode == RIGHT:
                env.y += PI/256
        if key == 'z':
            env.z -= PI/256
        if key == 'x':
            env.z += PI/256

def reset():
    if keyPressed is True:
        if key == 'r':
            env.x = 0.3927
            env.y = 0
            env.z = 1.2395
            env.eyeZ = (h/2.0) / tan(PI*30.0 / 180.0)
            env.centerX = w/2
            env.centerY = h/2

                                        
class env(object):    
    x = 0
    y = 0
    z = 0
    eyeX = w/2
    eyeY = h/2
    eyeZ = (h/2.0) / tan(PI*30.0 / 180.0)
    centerX = w/2
    centerY = h/2
    centerZ = 0
    upX = 0
    upY = 1
    upZ = 0
    count = 0
    value = 0
    num_ants = 0
    
    def __init__(self):
        pass
                                        
class room(object):
    
    num_rooms = 0
    
    def __init__(self, name, x, y, z):
        self.name = name
        self.x = x
        self.y = y
        self.z = z
        self.is_start = False
        self.is_end = False
        self.link = []
        self.move = []

    def set_start(self):
        self.is_start = True

    def set_end(self):
        self.is_end = True

    def add_link(self, room):
        self.link.append(room)
        
    def get_name(self):
        return self.name
    
    def set_move(self, move):
        self.move.append(move) 
        
    def __str__(self):
        return self.name
