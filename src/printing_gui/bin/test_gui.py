import Tkinter
import tkMessageBox
from Tkinter import *
#from PIL import ImageTk, Image
import os
import tkFont
import subprocess
import tkFileDialog
import shutil
import pickle
classlist=[]
a={}
b={}
c={}


def counted(fn):
    def wrapper(*args, **kwargs):
        wrapper.called += 1
        return fn(*args, **kwargs)
    wrapper.called = 0
    wrapper.__name__ = fn.__name__
    return wrapper

@counted
def id():
    return

@counted
def row_id():
    return

def reset_row():
    row_id.called=0
    return

def get_id(self):
    id()
    self.id=id.called
    return self.id

def get_row_id(self):
    row_id()
    self.id=row_id.called
    return self.id

#function build entry field with label an unit
def build_ent(input,fr):
    a[input.id] = Label(fr, text=input.n,width=15,anchor=W)
    a[input.id].grid(row=input.r, sticky=W)
    b[input.id] = Entry(fr, bd=2,width=6)
    b[input.id].insert(0,input.d)
    b[input.id].grid(row=input.r, column=1)
    c[input.id]=Label(fr,text=input.u,width=5)
    c[input.id].grid(row=input.r,column=2,sticky=W)

#function build headline
def build_headl(input,fr):
    a[input.id]=Label(fr,text=input.n,width=26,anchor=W)
    a[input.id].grid(row=input.r,sticky=W, columnspan=3)

#function build checkbutton
def build_ckbtn(input,fr):
    b[input.id]=StringVar()
    b[input.id].set(input.d)
    a[input.id]=Checkbutton(fr, text=input.n, variable=b[input.id])
    a[input.id].grid(row=input.r,sticky=W,columnspan=3)

#function build optionmenu
def build_opmenu(input,fr):
    b[input.id]=StringVar(fr)
    b[input.id].set(input.d)
    b[input.id].trace("w",hide)
    a[input.id]=apply(OptionMenu, (fr, b[input.id]) + tuple(input.o))
    a[input.id].grid(row=input.r,sticky=EW,columnspan=2)
    c[input.id]=Label(fr,text="",width=5)
    c[input.id].grid(row=input.r,column=2,sticky=W)

#function build empty row
def spacer(fr,row,col):
    Label(fr,text="",width=26,height=1).grid(row=row,column=col,sticky=W, columnspan=3)

#class headline:
class headl(object):
    """docstring for ipt."""
    def __init__(self,name):
        self.t = "headl"
        self.n = name
        self.r=[]
        self.id=[]
    def remove(self):
        a[self.id].grid_remove()
    def rebuild(self):
        a[self.id].grid()

#clas entry field
class ent(object):
    """docstring for ipt."""
    def __init__(self,name,default,unit):
        self.t = "ent"
        self.n = name
        self.d = default
        self.u = unit
        self.r=[]
        self.id=[]
    def get(self):
        return b[self.id].get()
    def remove(self):
        a[self.id].grid_remove()
        b[self.id].grid_remove()
        c[self.id].grid_remove()
    def rebuild(self):
        a[self.id].grid()
        b[self.id].grid()
        c[self.id].grid()

#class checkbutton
class ckbtn(object):
    """docstring for ipt."""
    def __init__(self,name,default):
        self.t = "ckbtn"
        self.n = name
        self.d = default
        self.r=[]
        self.id=[]
    def get(self):
        return b[self.id].get()
    def remove(self):
        a[self.id].grid_remove()
    def rebuild(self):
        a[self.id].grid()

#class optionmenu
class opmenu(object):
    """docstring for ipt."""
    def __init__(self,default,*options):
        self.t = "opmenu"
        self.d = options[default]
        self.o=options
        self.r=[]
        self.id=[]
    def get(self):
        return b[self.id].get()
    def remove(self):
        a[self.id].grid_remove()
    def rebuild(self):
        a[self.id].grid()

#class
class iptbox:
    """docstring for iptbox."""
    def __init__(self, frame,arg):
        classlist.append(self)
        self.list=arg
        self.f=frame
        for i in range(0,len(arg)):
            arg[i].r=get_row_id(self)
            arg[i].id=get_id(self)
            try:
                # Load the dictionary back from the pickle file.
                default_file="default\\"+str(arg[i].id)+".p"
                arg[i].d = pickle.load( open(default_file, "rb" ) )
                #print default
            except:
                print arg[i].id
                print "loading default fail"

            if arg[i].t=="opmenu":
                build_opmenu(arg[i],frame)
            if arg[i].t=="ent":
                build_ent(arg[i],frame)
            if arg[i].t=="ckbtn":
                build_ckbtn(arg[i],frame)
            if arg[i].t=="headl":
                build_headl(arg[i],frame)
        reset_row()
    def get(self,*arg):
        values={}
        for i in range(0,len(self.list)):
            if self.list[i].t=="headl":
                pass
            else:
                values[i]=self.list[i].get()
        return values

def get_all_values():

    for i in range(1,id.called):
        try:
            e[i]=b[i].get()
        except KeyError:
            pass
    return e

def StartPatran():
    top.quit()
    set_default()

def set_default():
    if not os.path.exists("default"):
        os.makedirs("default")
    try:
        pickle.dump( directory.get(), open( "default\\directory.p", "wb" ) )
    except:
        pass
    for i in range(0,len(classlist)):
        for m in range(0,len(classlist[i].list)):
            try:
                default_file = classlist[i].list[m].get()
                print default_file
                def_name=classlist[i].list[m].id
                def_file="default\\"+str(def_name)+".p"
                print def_file
                pickle.dump( default_file, open( def_file, "wb" ) )
                print 'saved'
            except:
                print 'not saved'

def reset(*arg):
    calc_all_str.remove()
    print "da hat sich was getraced!!"

def hide(*arg):
    print "***hide***"
    if anatyp.get()=="Buckling":
        loadincr.remove()
        itperupdt.remove()
        itperincr.remove()
        maxiter.remove()
        apprmeth.remove()
        methhead.remove()
        rootnum.rebuild()
    if anatyp.get()=="Non-Linear":
        methhead.rebuild()
        apprmeth.rebuild()
        if apprmeth.get()=="Newton":
            rootnum.remove()
            maxiter.remove()
            loadincr.rebuild()
            itperupdt.rebuild()
            itperincr.rebuild()
        if apprmeth.get()=="Arc-Length":
            rootnum.remove()
            maxiter.rebuild()
            loadincr.remove()
            itperupdt.remove()
            itperincr.remove()

def browse_directory():
    folder=tkFileDialog.askdirectory()
    directory.set(folder)

#function for layer entries
#will be rebuild cause dirty hardstyle programming
layerori={}
laydefaults={}
laydefaults[0]=[90.,45.,0.,-45.,-45.,0.,45.,90.,90.,45.,0.,-45.,-45.,0.,45.,90.]
laydefaults[1]=[90.,45.,0.,-45.,-45.,0.,45.,90.,90.,45.,0.,-45.,-45.,0.,45.,90.]
def layerorient():

	orienttop=Tkinter.Tk()
	numstr=int(str_lay.get())+1
	numskin=int(skin_lay.get())+1
	heorto = Label(orienttop, text="Set Orientation")
	heorto.grid(columnspan=3)
	headstringer = Label(orienttop, text="STRINGER:",anchor=W)
	headstringer.grid(row=1,columnspan=2,column=0,sticky=EW)
	headstringer = Label(orienttop, text="SKIN:",anchor=W)
	headstringer.grid(row=1,column=2,columnspan=2,sticky=EW)
	laystrlab={}
	laystrent={}
	laysklab={}
	layskent={}

	def saveori():
		savedstr={}
		savedskin={}
		numcol=1
		for i in range(1,numstr):
			layerori[0,i-1]=laystrent[i].get()
			laystrent[i].grid_forget()
			savedstr[i]=Label(orienttop, text=layerori[0,i-1],width=6)
			savedstr[i].grid(row=i+1, column=numcol)
			laydefaults[0][i-1]=layerori[0,i-1]
		numcol=3
		for i in range(1,numskin):
			layerori[1,i-1]=layskent[i].get()
			layskent[i].grid_forget()
			savedskin[i]=Label(orienttop, text=layerori[1,i-1],width=6)
			savedskin[i].grid(row=i+1, column=numcol)
			laydefaults[1][i-1]=layerori[1,i-1]
		savebt.grid_forget()
		orienttop.quit()
		closebt=Tkinter.Button(orienttop, text ="close", command = orienttop.destroy)
		closebt.grid(row=19,column=1,columnspan=2,sticky=EW)


	for i in range(1,numstr):
		numcol=1
		strnum=str(i)
		laystrlab[i] = Label(orienttop, text="Layer "+strnum,width=8)
		laystrlab[i].grid(row=i+1,column=numcol-1,sticky=W)
		laystrent[i] = Entry(orienttop, bd =2,width=6)
		laystrent[i].insert(0,laydefaults[0][i-1])
		laystrent[i].grid(row=i+1, column=numcol)
	for i in range(1,numskin):
		numcol=3
		strnum=str(i)
		laysklab[i] = Label(orienttop, text=strnum,width=8)
		laysklab[i].grid(row=i+1,column=numcol-1,sticky=W)
		layskent[i] = Entry(orienttop, bd =2,width=6)
		layskent[i].insert(0,laydefaults[1][i-1])
		layskent[i].grid(row=i+1, column=numcol)

	savebt=Tkinter.Button(orienttop, text ="save", command = saveori)
	savebt.grid(row=19,column=1,columnspan=2,sticky=EW)
	orienttop.mainloop()

#objekte erstellen
geohead=headl("PANEL GEOMETRY")
panelwidth=ent("panel width:",400,"mm")
panellength=ent("panel length:",500,"mm")
stringerheight=ent("stringer height:",37,"mm")
stringerwidth=ent("stringer width:",55,"mm")
stringerdist=ent("stringer distace:",150,"mm")
stringernum=ent("number of stringer:",3,"")
faulthead=headl("MANUFACTION FAULTS")
defect_str=ent("defected stringer:",1,"")
pos_fault=ent("position fault:",0,"mm")
rot_fault=ent("rotation fault:",0,"mm")
high_fault=ent("height fault:",0,"mm")
varhead=headl("VARIATION OPTIONS")
var_defects=ckbtn("variation of defects",0)
calc_all_str=ckbtn("calculate all stringer:",0)
all_errors=ckbtn("calculate all faults:",0)
var_steps=ent("variation steps:",1,"")
mathead=headl("MATERIAL")
chmat=opmenu(1,"Aluminium","Composite")
comphead=headl("COMPOSITE PROPERTIES")
ef11=ent("E-Modul-f11:",132000,"MPa")
ef22=ent("E-Modul-f22:",5700,"MPa")
gf12=ent("G-Modul-f12:",5100,"MPa")
nuf21=ent("nu_f21:",0.284,"")
layhead=headl("NUMBER OF LAYERS")
str_lay=ent("stringer layer",16,"")
skin_lay=ent("skin layer",16,"")
anahead=headl("ANALYSIS TYP")
methhead=headl("Method")
anatyp=opmenu(1,"no analysis","Non-Linear","Buckling","automatic")
apprmeth=opmenu(0,"Newton","Arc-Length")
loadincr=ent("load increments:",5,"")
itperupdt=ent("iterations per update:",20,"")
itperincr=ent("iterations per increment:",30,"")
rootnum=ent("number of roots:",5,"")
maxiter=ent("max. increment steps:",20,"")
forcehead=headl("FORCE")
forcex=ent("x-direction",20000,"N")
forcey=ent("y-direction",0,"N")
forcez=ent("z-direction",0,"N")
failhead=headl("FAILURE ANALYSISTYP")
failmenu=opmenu(1,"None","Maximum Stress","Tsai-Wu","Puck")
edghead=headl("ELEMENTS")
edglength=ent("Global Edge Length:",3,"")
pcidhead=headl("PC-ID:")
pcid=opmenu(0,"cip07","cip06","privat")
save_results=ckbtn("run matlab report",0)
mpctype=opmenu(1,"RBE2","RBE3")
failtype=opmenu(1,"progressive","first ply failure")

top = Tkinter.Tk()

#create frames/ object classification
#geometrie
geofr=Frame(top,bd=6,relief=GROOVE)
geofr.grid(row=0)
geo_list=[geohead,panelwidth,panellength,stringerheight,stringerwidth,stringerdist,stringernum]
geobox=iptbox(geofr,geo_list)
spacer(geofr,len(geo_list)+1,0)

#manufaction faults
faultfr=Frame(top,bd=6,relief=GROOVE)
faultfr.grid(row=1,rowspan=2)
fault_list=[faulthead,defect_str,pos_fault,rot_fault,high_fault,varhead,var_defects,calc_all_str,all_errors,var_steps]
faultbox=iptbox(faultfr,fault_list)

#material
matfr=Frame(top,bd=6,relief=GROOVE)
matfr.grid(row=3)
mat_list=[mathead,chmat,comphead,ef11,ef22,gf12,nuf21,layhead,str_lay,skin_lay]
matbox=iptbox(matfr,mat_list)
laybt= Tkinter.Button(matfr, text ="set orientation", command = layerorient)
laybt.grid(row=id.called+1,column=0,sticky=W+E,columnspan=3)

#analysistyp
anafr=Frame(top,bd=6,relief=GROOVE)
anafr.grid(row=0,column=1,sticky=N)
ana_list=[anahead,anatyp,methhead,apprmeth,loadincr,itperupdt,itperincr,rootnum,maxiter]
anabox=iptbox(anafr,ana_list)

#force
forcefr=Frame(top,bd=6,relief=GROOVE)
forcefr.grid(row=1,column=1,sticky=N)
force_list=[forcehead,forcex,forcey,forcez,failhead,failmenu]
forcebox=iptbox(forcefr,force_list)

#global edge length
edgfr=Frame(top,bd=6,relief=GROOVE)
edgfr.grid(row=2,column=1,sticky=S)
edg_list=[edghead,edglength,pcidhead,pcid,save_results,mpctype,failtype]
edgbox=iptbox(edgfr,edg_list)

#database name
directory=StringVar()

try:
    directory.set(pickle.load( open('default\\directory.p', "rb" ) ))
except:
    directory.set(os.curdir)
basefr=Frame(top,bd=6,relief=GROOVE)
basefr.grid(row=3,column=1,sticky=N)
dbaselab = Label(basefr, text="DATABASE NAME:",width=26,anchor=W)
dbaselab.grid(sticky=W,row=0)
dbase = Entry(basefr, bd =2,width=29)
dbase.insert(0,"database_01")
dbase.grid(row=1, column=0,sticky=EW)
browse_dir=Tkinter.Button(basefr, text ="browse", command = browse_directory)
browse_dir.grid()
direct=Label(basefr, textvariable=directory,width=27,anchor=E)
direct.grid()

#start button
#spacer(basefr,2,0)
helv36 = tkFont.Font(family='Helvetica', size=16, weight=tkFont.BOLD)
B= Tkinter.Button(basefr, text ="Start Patran", command = StartPatran,width=13,height=2,font=helv36)
B.grid()
#spacer(basefr,4,0)



#image
#path="C:\Users\digga\Documents\Studienarbeit\mscsoftwareklein.png"
#img = ImageTk.PhotoImage(Image.open(path))
#pic=Label(basefr,image=img,height=69)
#pic.grid(column=0,row=5,sticky=SW)

hide()
top.mainloop()
fault_info={}
decl={}
func_head='function panel()'
decl[0]='global real XFK1_E_m, XFK1_nu_m, XFK1_E_f11, XFK1_E_f22, XFK1_G_f12, XFK1_nu_f21, XFK1_nu_f23, XFK1_fvf'
decl[1]='global real l_panel, b_panel,b_stringer, h_stringer, d_stringer, force_x, force_y'
decl[2]='global real alu_thickness_skin, alu_thickness_stringer'
decl[3]='global real orient_stringer(virtual), orient_skin(virtual), ply_thickness'
decl[4]='global integer calc_all_stringer, num_layers_stringer, num_layers_skin, n_stringer,chosen_material,patran_quit'
decl[5]='global integer maxincresteps,num_roots,it_per_incre,it_per_update,def_num_stringer,save_results'
decl[6]='global integer var_error, num_iteration, side_sup, failure, max_gledl,gl_ed_l,plate_offset,def_one_side'
decl[7]='global string script_path[256],approx_method[20],element_typ[32](1), db_name[128], file_name[256], analysis_type[32],databasename[64],pc_id[8],result_path[256],db_path[256],mpctype[5],failure_type[12]'
decl[8]='global real def_pos_stringer, def_alpha, def_h_stringer,lc_load,load_increments'
t1='analysis_type="'
t2=anatyp.get()
t3='"'
decl[9]=t1.strip()+t2.strip()+t3.strip()
t1='databasename="'
t2=dbase.get()
decl[10]=t1.strip()+t2.strip()+t3.strip()
t1='pc_id="'
t2=pcid.get()
decl[11]=t1.strip()+t2.strip()+t3.strip()
t1='l_panel='
t2=panelwidth.get()
decl[12]=t1.strip()+t2.strip()
t1='b_panel='
t2=panellength.get()
decl[13]=t1.strip()+t2.strip()
t1='b_stringer='
t2=stringerwidth.get()
decl[14]=t1.strip()+t2.strip()
t1='h_stringer='
t2=stringerheight.get()
decl[15]=t1.strip()+t2.strip()
t1='d_stringer='
t2=stringerdist.get()
decl[16]=t1.strip()+t2.strip()
t1='n_stringer='
n_stringer=stringernum.get()
t2=n_stringer
decl[16]=t1.strip()+t2.strip()
decl[17]='side_sup=0'
t1='save_results='
t2=save_results.get()
decl[18]=t1.strip()+t2.strip()
t1='def_num_stringer='
defected_stringer=defect_str.get()
t2=defected_stringer
fault_info[1]=t1.strip()+t2.strip()
t1='def_pos_stringer='
position_fault=pos_fault.get()
t2=position_fault
fault_info[2]=t1.strip()+t2.strip()
t1='def_alpha='
rotation_fault=rot_fault.get()
t2=rotation_fault
fault_info[3]=t1.strip()+t2.strip()
t1='def_h_stringer='
heigth_fault=high_fault.get()
t2=heigth_fault
fault_info[4]=t1.strip()+t2.strip()
decl[23]='def_one_side=1'
t1='calc_all_stringer='
all_stringer=calc_all_str.get()
t2=all_stringer
fault_info[5]=t1.strip()+t2.strip()
t1='var_error='
variation_of_defects=var_defects.get()
t2=variation_of_defects
fault_info[6]=t1.strip()+t2.strip()
t1='num_iteration='
num_iterations=var_steps.get()
t2=num_iterations
fault_info[7]=t1.strip()+t2.strip()
t1='failure='
if failmenu.get()==failmenu.o[0]:
    t2=str(0)
if failmenu.get()==failmenu.o[1]:
    t2=str(1)
if failmenu.get()==failmenu.o[2]:
    t2=str(2)
decl[27]=t1.strip()+t2.strip()
t1='force_x='
t2=forcex.get()
decl[28]=t1.strip()+t2.strip()
t1='force_y='
t2=forcey.get()
decl[29]=t1.strip()+t2.strip()
t1='d_stringer='
t2=stringerdist.get()
decl[30]=t1.strip()+t2.strip()
t1='chosen_material='
if chmat.get()==chmat.o[0]:
    t2=str(0)
if chmat.get()==chmat.o[1]:
    t2=str(1)
decl[31]=t1.strip()+t2.strip()
decl[32]='plate_offset=0'
t1='num_layers_skin='
t2=skin_lay.get()
decl[33]=t1.strip()+t2.strip()
t1='num_layers_stringer='
t2=str_lay.get()
decl[34]=t1.strip()+t2.strip()
decl[35]='alu_thickness_skin=2.25'
decl[36]='alu_thickness_stringer=2.25'
decl[37]='ply_thickness=0.140625'
decl[38]='sys_allocate_array(orient_skin,1,num_layers_skin)'
decl[39]='sys_allocate_array(orient_stringer,1,num_layers_stringer)'
decl[40]='orient_skin=[90.,45.,0.,-45.,-45.,0.,45.,90.,90.,45.,0.,-45.,-45.,0.,45.,90.]'
decl[41]='orient_stringer=[90.,45.,0.,-45.,-45.,0.,45.,90.,90.,45.,0.,-45.,-45.,0.,45.,90.]'
t1='XFK1_E_f11='
t2=ef11.get()
decl[42]=t1.strip()+t2.strip()
t1='XFK1_E_f22='
t2=ef22.get()
decl[43]=t1.strip()+t2.strip()
t1='XFK1_G_f12='
t2=gf12.get()
decl[44]=t1.strip()+t2.strip()
t1='XFK1_nu_f21='
t2=nuf21.get()
decl[45]=t1.strip()+t2.strip()
decl[46]='element_typ(1)="Quad4"'
t1='gl_ed_l='
t2=edglength.get()
decl[47]=t1.strip()+t2.strip()
t1='patran_quit='
t2=save_results.get()
decl[48]=t1.strip()+t2.strip()
t1='approx_method="'
if apprmeth.get()==apprmeth.o[0]:
    t2=apprmeth.o[0]
if apprmeth.get()==apprmeth.o[1]:
    t2=apprmeth.o[1]
decl[49]=t1.strip()+t2.strip()+t3.strip()
t1='load_increments='
t2=loadincr.get()
decl[50]=t1.strip()+t2.strip()
t1='it_per_update='
t2=itperupdt.get()
decl[51]=t1.strip()+t2.strip()
t1='it_per_incre='
t2=itperincr.get()
decl[52]=t1.strip()+t2.strip()
t1='num_roots='
t2=rootnum.get()
decl[53]=t1.strip()+t2.strip()
t1='maxincresteps='
t2=maxiter.get()
decl[54]=t1.strip()+t2.strip()
t1='result_path="'
t4="\\report"
t2=directory.get()

t2=t2.strip()+t4.strip()
nf="\\"
t2=t2.strip()+nf.strip()+dbase.get()

report_path=t2
if not os.path.exists(t2):
	os.makedirs(t2)
decl[55]=t1.strip()+t2.strip()+t3.strip()
t1='db_path="'
t4="\db"
t2=directory.get()
t2=t2.strip()+t4.strip()
t2=t2.strip()+nf.strip()+dbase.get()
db_path=t2

if not os.path.exists(t2):
	os.makedirs(t2)
decl[56]=t1.strip()+t2.strip()+t3.strip()
t1='mpctype="'
t2=mpctype.get()
decl[57]=t1.strip()+t2.strip()+t3.strip()
t1='failure_type="'
t2=failtype.get()
decl[58]=t1.strip()+t2.strip()+t3.strip()
t1='script_path="'
script_path=os.path.dirname(os.path.abspath(__file__))
t2=script_path
decl[59]=t1.strip()+t2+t3.strip()




#write input report files

f=open('panel.ini','w+')
f.write(func_head)
f.write("\n")

for i in range (0, 61):
    try:
        (f.write(decl[i]))
        f.write("\n")
        i +=1
    except:
        print"writing fail, line:",i
        pass
f.close()



#ipt_file=cur_dir.strip()+"
db_name=dbase.get()
report_file=report_path.strip()+"\\input_report_"+db_name.strip()+".txt"
f=open(report_file,'w+')
for i in range (9, len(decl)+1):
    try:
        (f.write(decl[i]))
        f.write("\n")
        i +=1
    except:
        print"writing fail:",i
        pass
for i in range (1, 8):
    try:
        (f.write(fault_info[i]))
        f.write("\n")
        i +=1
    except:
        print"writing fail:",i
        pass
f.close()
shutil.copyfile(report_file, "input_report.txt")
top.destroy()


def read_buckling_factor():
	try:
		f=open('config.txt','r')
		f.readline()
		buckl=f.readline()
		f.close()
		buckl=float(buckl)
		return buckl
	except:
		print 'failed'
		return 0.0
 
def append_panel_pcl():
    shutil.copyfile("panel.ini", "panel.pcl")
    f=open('panel.pcl','a')
    t1='def_num_stringer='
    t2=defected_stringer
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='def_pos_stringer='
    t2=position_fault
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='def_alpha='
    t2=rotation_fault
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='def_h_stringer='
    t2=heigth_fault
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='calc_all_stringer='
    t2=all_stringer
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='var_error='
    t2=variation_of_defects
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='num_iteration='
    t2=num_iterations
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    t1='lc_load='
    t2=str(lc_load)
    f.write(t1.strip()+t2.strip())
    f.write("\n")
    f.write('calcpanel()')
    f.write("\n")
    f.write('end function')
    f.close()



def remove_dbase():
    if os.path.exists(db_path):
        try:
            shutil.rmtree(db_path, ignore_errors=False)
        except:
            pass
        if not os.path.exists(db_path):
            os.makedirs(db_path)

if all_stringer=='0':
    n_stringer=1

if anatyp.get()=="automatic":
    n_s=int(n_stringer)
    n_i=int(num_iterations)
    v_d=int(variation_of_defects)
    p_f=float(position_fault)
    r_f=float(rotation_fault)
    h_f=float(heigth_fault)
    a_e=int(all_errors.get())
    er_vec=[]
    if a_e==1:
        a_e=3
    else:
        a_e=1
        er_vec=[1,1,1]
    first_run=False
    for i in range(0,a_e):
        if a_e==3:
            er_vec=[0,0,0]
            er_vec[i]=1
        for n in range (1,n_s+1):
            for v in range(1,n_i+1):
                if first_run==False:
                    first_run=True
                    lc_load=0.0
                else:
                    lc_load=read_buckling_factor()
                if all_stringer=="1":
                    defected_stringer=str(n)
                position_fault=str(p_f/n_i*v*er_vec[0])
                rotation_fault=str(r_f/n_i*v*er_vec[1])
                heigth_fault=str(h_f/n_i*v*er_vec[2])
                num_iterations=str(v)
                append_panel_pcl()
                #print v
                subprocess.check_output(['Patran','-l'])
                remove_dbase()


else:
    all_stringer='0'
    lc_load=0
    append_panel_pcl()
    subprocess.check_output(['Patran','-l'])
    #append_panel_pcl()

print 'input report saved'
print 'start patran'
#start patran
#subprocess.check_output(['Patran','-l'])
#try:
    #shutil.rmtree(db_path, ignore_errors=True)
#except:
    #pass

print "running matlab"

if anatyp.get()=="Buckling":
    if save_results.get()==1:
        print 'start matlab'
        DosCmd = 'matlab -nosplash -nodesktop -wait -r "Bucklingmodes";quit'
        os.system(DosCmd)
print 'ready'

