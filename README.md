# CPF-Gen
Gerador de Números Aleatórios de CPF

Compilando:

	$ make
	gcc cpfgen.c -o cpfgen

Exemplos:

	$ ./cpfgen
	12758151200

	$ ./cpfgen -f
	858.935.757-09

	$ ./cpfgen -n 10
	83021679242
	63741739375
	07776155179
	09699700211
	34309916333
	41423625188
	30855962089
	17644946365
	52325447057
	71164186361

	$ ./cpfgen -n 10 -f
	914.423.927-03
	844.802.747-74
	661.477.681-90
	878.971.745-73
	740.248.162-09
	967.865.451-22
	292.159.316-51
	069.315.327-07
	935.179.293-52
	048.109.433-48
