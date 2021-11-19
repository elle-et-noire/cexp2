#%matplotlib nbagg
"""
2D Wave Equation
一様媒質: 位相速度が時間・空間的に一定
FTCS法
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import ArtistAnimation # アニメーション作成のためのメソッドをインポート


c=1
print ("c=",c)
Lx = 1 # 長さ[m]
Ly = 1
t_max = 0.5

Nx = 41
Ny =41

delta_x = Lx/Nx
delta_y = Ly/Ny
delta_t=(1/(1/delta_x+1/delta_y))/c*0.5 #時間刻み幅。あるていど小さめにとる。

print("delta_t=",delta_t)

Nt = int(t_max/delta_t)


print("Nt=",Nt)

stx=delta_x/delta_t
sty=delta_y/delta_t



u =  np.empty((Nx,Ny,Nt),dtype=float)

#境界条件
u[0,:,:], u[-1,:,:] , u[:,0,:] , u[:,-1,:] = 0, 0, 0, 0

#初期条件
for i in range (Nx) :
    for ii in range(Ny):
        u[i,ii,0]  = (np.exp(-((i*delta_x-Lx/2)**2+(ii*delta_y-Ly/2)**2)/0.01))  #初期条件。ガウス分布関数の設置。

#波動 u[i,ii,1]を作るための計算。初期条件2を中心差分して得られる。
for i in range(1,Nx-1): 
    for ii in range(1,Ny-1):
        u[i,ii,1]= u[i,ii,0]+0.5*((delta_t/delta_x)**2)*(c**2)*(u[i+1,ii, 0]+u[i-1, ii,0]-2*u[i,ii,0])\
+0.5*((delta_t/delta_y)**2)*(c**2)*(u[i,ii+1, 0]+u[i,ii-1, 0]-2*u[i,ii,0])


# #波動の時間発展のためのループ
for j in range(1,Nt-1):
    for i in range(1,Nx-1):
        for ii in range(1,Ny-1):
            u[i,ii, j+1] = 2*u[i,ii,j]-u[i,ii,j-1]+((c/stx)**2)* (u[i+1,ii,j]+u[i-1,ii,j]\
-2*u[i,ii,j])+((c/sty)**2)* (u[i,ii+1,j]+u[i,ii-1,j]-2*u[i,ii,j]) 

#可視化のためのプログラム

#%matplotlib nbagg 
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation # アニメーション作成のためのメソッドをインポート

fig = plt.figure(figsize = (8, 6))
ax = fig.gca(projection='3d')

x=list(range(Nx))
y=list(range(Ny))
X, Y = np.meshgrid(x,y)

def update(i,u,fig_title):
    if i != 0:
        ax.clear()
    ax.view_init(elev=60., azim=60.) # アングル設定
    #ax.plot_surface(X,Y,u[X,Y,i],rstride=1,cstride=1,cmap='Greys',linewidth=0.3) # サーフェスプロット
    ax.plot_wireframe(X,Y,u[X,Y,i],rstride=1,cstride=1,color='blue',linewidth=0.3) # ワイヤーフレーム表示

    ax.set_title(fig_title + 'i=' + str(i))
    ax.set_zlim(-0.4,0.4) # zの描画範囲の指定
    ax.set_xlabel('X') # ラベル
    ax.set_ylabel('Y')
    ax.set_zlabel('U')



    return ax


ani = animation.FuncAnimation(fig,update,fargs = (u,'Wave motion: time step='), interval =1, frames = Nt,blit=False)
fig.show()

ani.save("output.gif", writer="imagemagick")