import matplotlib.animation as animation  # アニメーション作成のためのメソッドをインポート
import matplotlib.pyplot as plt
import numpy as np

nt = 600
nx = 100
# u[t,x,y]
u = np.empty((nt, nx, nx), dtype = float)
# 伝播速度 (alpha^2 < 1/2 でないと安定しない)
alpha2 = 0.25
beta2 = 0.05 # 異なる速度
# 初期波面
for i in range(nx):
  for j in range(nx):
    a = 0.05
    u[0,i,j] = u[1,i,j] = 0.3*np.exp(-a*(i-nx*2/3)**2)

dirichlet = False
for n in range(1, nt - 1):
    for j in range(0, nx):
        for l in range(0, nx):
            if j == 0 or j == nx-1 or l == 0 or l == nx-1: # 境界は別処理
                continue
            v = 0.0
            if 0 <= j + l <= 50:
              v = beta2
            else:
              v = alpha2
            u[n+1,j,l] = 2*u[n,j,l]-u[n-1,j,l]+v*(
                u[n,j+1,l]-2*u[n,j,l]+u[n,j-1,l]+u[n,j,l+1]-2*u[n,j,l]+u[n,j,l-1])
    for j in range(0, nx):
        if dirichlet: # 固定端条件
            u[n + 1, j, 0] = u[n + 1, 0, j] = u[n + 1, j, nx - 1] = u[n + 1, nx - 1, j] = 0
        else: # 自由端条件
            u[n + 1, j, 0] = u[n + 1, j, 1]
            u[n + 1, 0, j] = u[n + 1, 1, j]
            u[n + 1, nx - 1, j] = u[n + 1, nx - 2, j]
            u[n + 1, j, nx - 1] = u[n + 1, j, nx - 2]


# 可視化のためのプログラム

# Figureを追加
fig = plt.figure(figsize = (10, 6))

# 3DAxesを追加
ax = fig.add_subplot(111, projection="3d")

# 軸ラベルを設定
ax.set_xlabel("x", size = 16)
ax.set_ylabel("y", size = 16)
ax.set_zlabel("z", size = 16)

# (x,y)データを作成
x = list(range(nx))
y = list(range(nx))

# 格子点の作成
X, Y = np.meshgrid(x, y)

def update(i):
  if i != 0:
    ax.clear()
  # ワイヤーフレームで描く
  ax.plot_wireframe(X, Y, u[i, X, Y], color = "darkblue")
  ax.set_title(f"FTCS - sq-wav-eq (alpha2=0.25, a=0.1, times step = {i})", size = 16)
  ax.set_zlim(-0.4, 0.4)  # zの描画範囲の指定
  return ax

ani = animation.FuncAnimation(fig, update, frames = nt, blit = False)

# plt.show()

ani.save("output.gif", writer = "pillow", fps = 30)
