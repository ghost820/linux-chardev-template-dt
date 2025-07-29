#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

MODULE_AUTHOR("Michal Miladowski <michal.miladowski@gmail.com>");
MODULE_DESCRIPTION("Character Device Driver Template");
MODULE_LICENSE("GPL");

static int pcdev_probe(struct platform_device *pdev)
{
    return 0;
}

static int pcdev_remove(struct platform_device *pdev)
{
    return 0;
}

static const struct platform_device_id chardev_id[] = {
	{ .name = "chardev-1", .driver_data = 0 },
	{}
};
MODULE_DEVICE_TABLE(platform, chardev_id);

static const struct of_device_id chardev_of_match[] = {
	{ .compatible = "org,chardev-1", .data = NULL },
	{}
};
MODULE_DEVICE_TABLE(of, chardev_of_match);

static struct platform_driver chardev_driver = {
	.driver	= {
		.name = "chardev",
		.of_match_table = chardev_of_match,
	},
	.probe = chardev_probe,
	.remove = chardev_remove,
	.id_table = chardev_id,
};
module_platform_driver(chardev_driver);
