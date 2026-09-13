% Parameter
L = 1;               % panjang dawai
T = 0.5;             % waktu maksimum
dx = 0.1;
dt = 0.05;
c = 2;               % kecepatan gelombang
r = c * dt / dx;     % rasio CFL (Courant number)
N = L/dx;            % jumlah segmen ruang
M = T/dt;            % jumlah langkah waktu
x = linspace(0, L, N+1);  % mesh ruang
u = zeros(N+1, M+1);      % solusi u(x,t)

% Kondisi awal u(x,0) = sin(pi*x) + sin(2*pi*x)
for i = 1:N+1
    u(i,1) = sin(pi * x(i)) + sin(2 * pi * x(i));
end

% Kondisi awal turunan waktu ut(x,0) = 0
% Menggunakan:
% u(i,2) = 0.5*(u(i-1,1) + u(i+1,1)) untuk i=2:N
for i = 2:N
    u(i,2) = 0.5 * (u(i-1,1) + u(i+1,1));
end

% Kondisi batas
u(1,:) = 0;      % u(0,t) = 0
u(end,:) = 0;    % u(1,t) = 0

% Iterasi waktu (j = 2 to M)
for j = 2:M
    for i = 2:N
        u(i,j+1) = u(i+1,j) + u(i-1,j) - u(i,j-1);
    end
end

% Plot hasil
[X, T] = meshgrid(0:dt:T, 0:dx:L);
surf(T, X, u)
xlabel('Waktu t')
ylabel('Posisi x')
zlabel('u(x,t)')
title('Simulasi Persamaan Gelombang 1D dengan Metode Finite Difference')