#include "../cub3dft.h"

int	main(int argc, char **argv)
{
	mlx_t	*mlx;

	(void)argv;
	if (argc != 2)
		return (printf("./cub3D <map_path>\n"));
	/*if (!ft_chek_args(argc, argv))
		return (printf("Error: Incorrecte arguments\n"));*/
	mlx = mlx_init(3840, 2160, "cub3D", true);
	(void)mlx;
	return (0);
}