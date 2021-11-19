# PYTHON_MATPLOTLIB_WIREFRAME

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d

# Figureを追加
fig = plt.figure(figsize = (10, 6))

# 3DAxesを追加
ax = fig.add_subplot(111, projection="3d")

# Axes(サブプロット)のタイトルを設定
ax.set_title("hyperbolic paraboloid", size = 16)

# 軸ラベルを設定
ax.set_xlabel("x", size = 16)
ax.set_ylabel("y", size = 16)
ax.set_zlabel("z", size = 16)

# (x,y)データを作成
x = np.linspace(-8, 8, 256)
y = np.linspace(-8, 8, 256)

# 格子点の作成
X, Y = np.meshgrid(x, y)

# 高度の計算式
Z = X**2 - Y**2

# ワイヤーフレームで双曲放物面(hyperbolic paraboloid)を描く
ax.plot_wireframe(X, Y, Z, color = "darkblue")

plt.show()